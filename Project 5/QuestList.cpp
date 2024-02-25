// NAME: KEVIN WENG
// EMAIL: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// DATE: 10/29/23
// This is the Quest List implementation

#include "QuestList.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


// Quest::Quest(): quest_title_{""}, quest_description_{""}, quest_complete_{false}, experience_points_{0}, dependencies_{{}}, subquests_{{}};

QuestList::QuestList() : DoublyLinkedList<Quest*> () {
    
}

/**
    @param: a reference to string name of an input file
    @pre: Formatting of the csv file is as follows:
        Title: A string
        Description: A string
        Completion Status: 0 (False) or 1 (True)
        Experience Points: A non negative integer
        Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
        Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The dependencies and subquests are separated by a semicolon and may be NONE.
        - The dependencies and subquests may be in any order.
        - If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
            - Title: The title of the quest
            - Description: "NOT DISCOVERED"
            - Completion Status: False
            - Experience Points: 0
            - Dependencies: An empty vector
            - Subquests: An empty vector
        - However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
        Hint: update as needed using addQuest()
        

    @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.

*/

QuestList::QuestList(const std::string& file) {
    std::ifstream read(file);

    if (!read.is_open()) {
        std::cout << "ERROR: file can't be opened" << std::endl;
    }

    std::string temp_depend = "";
    std::string temp_subquest = "";
    std::string str;
    std::getline(read, str); // ignores the header of the csv file

    std::string title, description, dependencies, subquests;
    bool completion;
    int experience_points;
    std::string temp;

    std::string parse = "";
    std::vector <Quest*> empty_dependencies_vector; // empty vector
    std::vector <Quest*> empty_subquests_vector; // empty vector

    while (std::getline(read, parse)) {
        std::stringstream input_string(parse);

        // Quest Title
        getline(input_string, title, ',');
        
        // Description
        getline(input_string, description, ',');

        // Completion Status
        getline(input_string, temp, ',');
        std::istringstream(temp) >> completion;

        // Experience Points
        getline(input_string, temp, ',');
        std::istringstream(temp) >> experience_points;

        // Dependencies
        getline(input_string, dependencies, ',');
        std::vector <Quest*> empty_dependencies_vector; // empty vector
        std::string empty_string = "";

        std::istringstream dependencies_stream(dependencies);
        while (std::getline(dependencies_stream, temp_depend, ';')) {
            if (temp_depend != "NONE") {
                if (getPosOf(temp_depend) != -1) { // if the position != -1, which means there is something inside the linked list
                Node<Quest*> *dependency_node = getPointerTo(getPosOf(temp_depend)); // converts the int from getPosOf to a pointer
                empty_dependencies_vector.push_back(dependency_node -> getItem()); // pushes back the node's item (a quest) into the empty vector into the linked list
                
            } else {
                Quest* default_quest = new Quest; // creates a new object
                default_quest -> title_ = temp_depend; // sets the quest title to the title stored in temp_depend
                default_quest -> description_ = "NOT DISCOVERED"; // sets the quest description to "NOT DISCOVERED"
                default_quest -> completed_ = false; // sets the quest completion to false
                default_quest -> experience_points_ = 0; // sets the experience points to 0
                default_quest -> dependencies_ = {}; // sets the dependencies to a empty vector {}
                default_quest -> subquests_ = {}; // sets the subquest to a empty vector {}
                addQuest(default_quest); // adds the quest
                empty_dependencies_vector.push_back(default_quest); // adds the deafult_quest as a new quest
            }
            }
        }

        // Subquests
        getline(input_string, subquests, ',');
        std::vector <Quest*> empty_subquests_vector; // empty vector
        std::string empty_subquest_string = "";

        std::istringstream subquests_stream(subquests);
        while (getline(subquests_stream, temp_subquest, ';')) { // grabs the line stopping at the ';' and stores it in the parse variable
            if (temp_subquest != "NONE") {
                if (getPosOf(temp_subquest) != -1) { // if the position != -1, which means there is something inside the linked list
                Node<Quest*> *subquest_node = getPointerTo(getPosOf(temp_subquest)); // converts the int from getPosOf to a pointer
                empty_subquests_vector.push_back(subquest_node -> getItem()); // pushes back the node's item (a quest) into the empty vector into the linked list
            } else {
                Quest* default_quest = new Quest; // creates a new object
                default_quest -> title_ = temp_subquest; // sets the quest title to the title stored in temp_subquest
                default_quest -> description_ = "NOT DISCOVERED"; // sets the quest description to "NOT DISCOVERED"
                default_quest -> completed_ = false; // sets the quest completion to false
                default_quest -> experience_points_ = 0; // sets the experience points to 0
                default_quest -> dependencies_ = {}; // sets the dependencies to a empty vector {}
                default_quest -> subquests_ = {}; // sets the subquest to a empty vector {}
                addQuest(default_quest); // adds the quest
                empty_subquests_vector.push_back(default_quest); // adds the default_quest as a new quest
                
            }
        }   
    }
    addQuest(title, description, completion, experience_points, empty_dependencies_vector, empty_subquests_vector); // adds the quest containing the values into each of the variables
}
}
    /**
    @param: A string reference to a quest title
    @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
*/
    int QuestList::getPosOf(const std::string& quest_title) const {
        Node<Quest*>* new_node = first_; // new pointer that points to the first node
        int position = 0;

        while(new_node != nullptr) {
            if (new_node -> getItem() -> title_ == quest_title) { // checks to see if the title = to the title being inputted
                return position;
            } else {
                position++;
                new_node = new_node -> getNext(); // setting the current node to the next node
            }
        }
        return -1; // returns -1 if the quest title isn't in the linked list
    }

   
   /**
    @param: A string reference to a quest title
    @return: True if the quest with the given title is already in the QuestList
*/
    bool QuestList::contains(const std::string& quest_title) const {
        return getPosOf(quest_title) != -1;
    }

    
    /**
    @pre: The given quest is not already in the QuestList
    @param:  A pointer to a Quest object
    @post:  Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
           
    @return: True if the quest was added or updated successfully, False otherwise
*/
    bool QuestList::addQuest(Quest* add) {
        if (contains(add -> title_) && (getPointerTo(getPosOf(add -> title_)) -> getItem()) -> description_ != "NOT DISCOVERED") {
            return false;
        } else if (contains(add -> title_) && (getPointerTo(getPosOf(add -> title_)) -> getItem()) -> description_ == "NOT DISCOVERED") {
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> description_ = add -> description_;
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> completed_ = add -> completed_;
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> experience_points_ = add -> experience_points_;
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> dependencies_ = add -> dependencies_;
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> subquests_ = add -> subquests_;
            return true;
        } else { 
            if(insert(getLength(), add)) { // gets the length of the quest list and adds the new quest
                for(auto i : add -> dependencies_) { // gets the dependency from add, auto auto-detects the data type of what ur comparing
                    if(!contains(i -> title_)) {
                        addQuest(i);
                    }
                }
                for(auto j : add -> subquests_) {
                    if(!contains(j -> title_)) {
                        addQuest(j);
                    }
                }
                return true;
                } else {
                    return false;
            }
        }
    }

    
    /**
    @param:  A reference to string representing the quest title
    @param:  A reference to string representing the quest description
    @param:  A reference to boolean representing if the quest is completed
    @param:  An reference to int representing experience points the quest rewards upon completion 
    @param:  A reference to vector of Quest pointers representing the quest's dependencies
    @param:  A reference to vector of Quest pointers representing the quest's subquests
    @post:   Creates a new Quest object and inserts a pointer to it into the QuestList. 
             If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
             Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
             

    @return: True if the quest was added or updated successfully, False otherwise

*/
    bool QuestList::addQuest(const std::string& title, const std::string& quest_description, const bool& quest_completion, const int& experience_points, const std::vector<Quest*>& dependencies, const std::vector<Quest*>& subquests) {
        Quest* quest = new Quest(title, quest_description, quest_completion, experience_points, dependencies, subquests); // creating a new quest individually
        return addQuest(quest);
    }

    
    /**
    @param:  A Quest pointer
    @return: A boolean indicating if all the given quest's dependencies are completed
*/
    bool QuestList::dependenciesComplete(Quest* dependencies) {
        for(int i = 0; i < dependencies -> dependencies_.size(); i++) {
            if(!(dependencies -> dependencies_[i] -> completed_)); // if each of the dependencies index's quest isn't complete, return false
            return false;
        }
        return true;  
    }


   /**
    @param: A Quest pointer
    @return: A boolean if the given quest is available.
    Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
*/
    bool QuestList::questAvailable(Quest* quest_available) {
        if (!dependenciesComplete(quest_available) || quest_available -> completed_) { // if the dependencies aren't completed or the actual quest is already completed, you return false
            return false;
        }
        return true;
    }

    
    /**
    @param: A Quest pointer
    @post: Prints the quest title and completion status
    The output should be of the form:
    [Quest Title]: [Complete / Not Complete]
    [Quest Description]\n\n
*/
    void QuestList::printQuest(Quest* print_quest) { 
        std::string complete = "";

        if (print_quest -> completed_) {
            complete = "Complete";
        } else {
            complete = "Not Complete";
        }

        std::cout << print_quest -> title_ << ": " << complete << "\n" // prints the quest's title and see if it's completed or not
        << print_quest -> description_ << "\n\n";
    }

    

/**
    @param: A string reference to a quest title
    @post:  Prints a list of quests that must to be completed before the given quest can be started (incomplete dependencies).
            If any of the quest's incomplete dependencies have an incomplete dependency, recursively print the quests that need to be done in order, indenting incomplete quests. 
            The indentation for incomplete quests is 2 spaces: "  "    
            The format of the list should be of the following forms for each different case:

            Query: [Quest Title]
            No such quest.
    
            Query: [Quest Title]
            Quest Complete
    
            Query: [Quest Title]
            Ready: [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
              [Quest Title]
            
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Dependency2]
              [Quest Title]
              
     If the given quest title is not found in the list, print "No such quest."
*/
    void QuestList::questQuery(const std::string& quest_title) { 
        std::cout << "Query: " << quest_title << "\n";

        if (!contains(quest_title)) { // checks to see if the quest exists
            std::cout << "No such quest.\n";
            return;
        }

        Quest* quest = getPointerTo(getPosOf(quest_title)) -> getItem();

        if (quest -> completed_) { // checks to see if the quest is completed
            std::cout << "Quest Complete\n";
            return;
        } else {
            questQuery_helper(quest);
        }
    }

    void QuestList::questQuery_helper(Quest* quest) {
        if (quest -> dependencies_.empty() || dependenciesComplete(quest)) { // checks to see if the quest's dependency is empty  or if the dependency is completed
            std::cout << "Ready: " << quest -> title_ << "\n"; // prints "Ready:" and the quest title if the dependency is either empty or complete
            return;
        }

        for (Quest* quest1 : quest -> dependencies_) {
            if (!quest1 -> completed_) {
                questQuery_helper(quest1); // recursively calls
            }
        }

        std::cout << "  " << quest -> title_ << "\n";
    }


/**
    @return: An integer sum of all the experience gained
    Note: This should only include experience from completed quests 
*/
    int QuestList::calculateGainedExperience() {
        int experience_points = 0;

        Node<Quest*> *node = first_;
        
        while (node != nullptr) {
            if (node -> getItem() -> completed_ ) { // checks to see if each quest is completed
                experience_points += node -> getItem() -> experience_points_; // adds the experience points from the completed quest into the experienced_points variable
            }
            node = node -> getNext(); // moves the node pointer to the next
        }
        return experience_points;
    }

 
 /**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
    Note: Also consider the potential experience if a subquest itself has subquests.
*/
    int QuestList::calculateProjectedExperience(Quest* main_quest) {
        int experience_points = 0;
        experience_points += main_quest -> experience_points_; // add the main quest experience points into the variable

        for (int i = 0; i < main_quest -> subquests_.size(); i++) {
            experience_points += calculateProjectedExperience(main_quest -> subquests_[i]); // keeps calling the function and adds the experience points of each subquest
        }
        return experience_points;
    } 

 /**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
    Note: Also consider the experience gained if a completed subquest itself has subquests.  
*/
    int QuestList::calculatePathwayExperience(Quest* main_quest) {
        int experience_points = 0; // initialize the value to 0
        
        if (main_quest -> completed_) {
            experience_points += main_quest -> experience_points_; // if the quest is completed, it will add it's experience points into the variable we created called "experience_points"
        }

        for (int i = 0; i < main_quest -> subquests_.size(); i++) {
            experience_points += calculatePathwayExperience(main_quest -> subquests_[i]); // adds the calculated pathway experience each of the main quest's subquests
        }
        return experience_points;
    }

    /**
    @param: A string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every quest in the list.
           With filter "COMPLETE":   Only print out the completed quests in the list.
           With filter "INCOMPLETE": Only print out the incomplete quests in the list.
           With filter "AVAILABLE":  Only print out the available quests in the list.
           If an invalid filter is passed, print "Invalid Filter\n"
    Printing quests should be of the form:
    [Quest title]: [Complete / Not Complete]  
    [Quest description]\n
*/
    void QuestList::questHistory(const std::string& filter) {
        if (filter != "NONE" && filter != "COMPLETE" && filter != "INCOMPLETE" && filter != "AVAILABLE") {
            std::cout << "Invalid Filter\n";
        }

        Node <Quest*> *temp_node = first_;

        while (temp_node != nullptr) {
            if (filter == "NONE") {
                printQuest(temp_node -> getItem()); // prints out the quest if the filter is "NONE"

            } else if (filter == "COMPLETE") {
                if(temp_node -> getItem() -> completed_) {
                    printQuest(temp_node -> getItem()); // prints out the quest if the filter is "COMPLETE"
                }
                
            } else if (filter == "INCOMPLETE") {
                if (!(temp_node -> getItem() -> completed_)) {
                    printQuest(temp_node -> getItem()); // prints out the quest if the filter is "INCOMPLETE"
                }

            } else if (filter == "AVAILABLE") {
                if (questAvailable(temp_node -> getItem())) {
                    printQuest(temp_node -> getItem()); // prints out the quest if the filter is "AVAILABLE"
                } 
            }
            temp_node = temp_node -> getNext(); // points the node to the next node
        }
    }

/**
    @param: A quest pointer to a main quest
    @post:  Outputs subquest pathway. Print quest names with two spaces ("  ") of indentation for each subquest, recursively.
            Also print the percentage of experience gained in this pathway, rounded down to the lower integer.
            The format should be of the form:
            [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
                [Subquest0]: [Complete / Not Complete]
                    [Sub-Subquest01]: [Complete / Not Complete]
                        [Sub-Subquest011]: [Complete / Not Complete]
                    [Subquest02]: [Complete / Not Complete]
            Hint: You can write a helper function to print the subquests recursively. If the given quest is already marked as completed, you can assume that all of its subquests are also completed.
*/
   void QuestList::quest_detail_helper(Quest* main_quest, int spaces) {
        std::string complete = "";

        for (int i; i < spaces; i++) {
            complete += " ";
        }

        for (int i = 0; i < main_quest -> subquests_.size(); i++) {
            quest_detail_helper(main_quest -> subquests_[i], spaces + 2);

            if (main_quest -> subquests_[i] -> completed_) {
                std::cout << complete << main_quest -> subquests_[i] -> title_ << ": Complete" << "\n";
            } else {
                std::cout << complete << main_quest -> subquests_[i] -> title_ << ": Not Complete" << "\n";
            }
        }
   }

    void QuestList::printQuestDetails(Quest* main_quest) {
        double projected_calculation = calculateProjectedExperience(main_quest);
        double pathway_calculation = calculatePathwayExperience(main_quest);

        std::cout << main_quest -> title_ << " (" << int((pathway_calculation / projected_calculation) * 100) << '%' << "Complete)" << std::endl;

        if (main_quest -> completed_) {
            return;
        }

        quest_detail_helper(main_quest, 2);

    }
