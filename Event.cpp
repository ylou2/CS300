#include <string>
#include <vector>
#include <iostream>
#include "date/date.h" 
#include <chrono>
class Event {
    private:
        std::string eventName;
        std::string eventDate;
        std::string location;
        std::vector<std::string> rsvpList;
    public:
        Event(std::string name, std::string date, std::string loc)
        : eventName(name), eventDate(date), location(loc) {}
        virtual std::string getDetails() const = 0;
        virtual bool isUpcoming() const = 0;
        void addRSVP(const std::string& username) {
            rsvpList.push_back(username);
        }
        std::vector<std::string> getRSVPList() const {
            return rsvpList;
        }
        int getRSVPCount() const {
            return rsvpList.size();
        }
        std::string getEventName() const {
            return eventName;
        }
        std::string getEventDate() const {
            return eventDate;
        }

        std::string getLocation() const {
            return location;
        }

        void setEventName(const std::string& name) {
            eventName = name;
        }

        void setEventDate(const std::string& date) {
            eventDate = date;
        }

        void setLocation(const std::string& loc) {
            location = loc;
        }
        virtual ~Event() = default;
};
class Workshop : public Event {

    private:
        std::string duration;
        std::string instructor;
    public:
        Workshop(std::string name, std::string date, std::string loc, std::string dur, std::string ins)
            : Event(name, date, loc), duration(dur), instructor(ins) {}
        std::string getDuration() const {
            return duration;
        }
        std::string getInstructor() const {
            return instructor;
        }
        void setDuration (const std::string &duration) {
            this->duration = duration;
        }
        void setInstructor (const std::string &instructor) {
            this->instructor = instructor;
        }
        std::string getDetails() const override {
            return "Workshop: " + getEventName() + " on " + getEventDate() + " at " + getLocation() + " in " + getDuration() + " by " + getInstructor();
        }
        bool isUpcoming() const override {
            //using floor to get date (rounded)
            auto today = date::floor<date::days>(std::chrono::system_clock::now());
            std::chrono::system_clock::time_point eventTimePoint;
            //parse string into std::chrono::time_point
            std::istringstream in{getEventDate()};
            in >> date::parse("%Y-%m-%d", eventTimePoint);
            return today < eventTimePoint;
        }
};
class Concert : public Event {
    private:
        std::string bandname;
        std::string genre;
    public:
        Concert(std::string name, std::string date, std::string loc, std::string band, std::string gen)
            : Event(name, date, loc), bandname(band), genre(gen){}
        std::string getBandname() const {
            return bandname;
        }
        std::string getGenre() const {
            return genre;
        }
        void setBandname(const std::string &bandname) {
            this->bandname = bandname;
        }
        void setGenre (const std::string &genre) {
            this->genre = genre;
        }
        std::string getDetails() const override{
            return "Concert: " + getEventName() + " on " + getEventDate() + " at " + getLocation() + " with genre " + getGenre() + " by " + getBandname();
        }
        bool isUpcoming() const override {
            auto today = date::floor<date::days>(std::chrono::system_clock::now());
            std::chrono::system_clock::time_point eventTimePoint;
            std::istringstream in{getEventDate()};
            in >> date::parse("%Y-%m-%d", eventTimePoint);
            return today < eventTimePoint;
        }
};
class Conference : public Event {
    private:
        std::string speakers;
        std::string topics;
    public:
        Conference(std::string name, std::string date, std::string loc, std::string spkrs, std::string tpcs)
            : Event(name, date, loc), speakers(spkrs), topics(tpcs){}
        void setSpeakers(const std::string &speakers) {
            this->speakers = speakers;
        }
        void setTopics(const std::string &topics) {
            this->topics = topics;
        }
        std::string getSpeakers() const {return speakers;}
        std::string getTopics() const {return topics;}
        std::string getDetails() const override {
            return "Conference: " + getEventName() + " on " + getEventDate() + " at " + getLocation() + " by " + getSpeakers() + " about " + getTopics();
        }
        bool isUpcoming() const override{
            auto today = date::floor<date::days>(std::chrono::system_clock::now());
            std::chrono::system_clock::time_point eventTimePoint;
            std::istringstream in{getEventDate()};
            in >> date::parse("%Y-%m-%d", eventTimePoint);
            return today < eventTimePoint;
        }
};
class EventFactory {
    public:
        virtual Event* createEvent(std::string name, std::string date, std::string loc, std::string additional1 = "", std::string additional2 = "") const = 0;
        virtual ~EventFactory() = default;
};
class WorkshopFactory : public EventFactory {
    public:
        Event* createEvent(std::string name, std::string date, std::string loc, std::string dur, std::string ins) const override {
            return new Workshop(name, date, loc, dur, ins);
        }
};
class ConcertFactory : public EventFactory {
    public:
        Event* createEvent(std::string name, std::string date, std::string loc, std::string band, std::string gen) const override {
            return new Concert(name, date, loc, band, gen);
        }
};
class ConferenceFactory : public EventFactory {
    public:
        Event* createEvent(std::string name, std::string date, std::string loc, std::string speakers, std::string topics) const override {
            return new Conference(name, date, loc, speakers, topics);
        }
};
class Search {
    public:
        virtual std::vector<Event*> searchEvent(std::vector<Event*> &events, std::string searchItem)  const = 0;
        virtual ~Search() = default;
};
class SearchDate : public Search {
    public:
        std::vector<Event*> searchEvent(std::vector<Event*> &events, std::string date) const override {
            //result of searching
            std::vector<Event*> result;
            for(auto event : events) {
                if(date == event->getEventDate()) {
                    result.push_back(event);
                }
            }
            return result;
        }
};
class SearchType : public Search {
    public:
        std::vector<Event*> searchEvent(std::vector<Event*> &events, std::string type) const override {
            std::vector<Event*> result;
            for(auto event : events) {
                if(type == "Workshop" && dynamic_cast<Workshop*>(event)) {
                    result.push_back(event);
                } else if (type == "Concert" && dynamic_cast<Concert*>(event)) {
                    result.push_back(event);
                }
            }
            return result;
        }
};
class SearchLocation : public Search {
    public:
        std::vector<Event*> searchEvent(std::vector<Event*> &events, std::string loc) const override {
            std::vector<Event*> result;
            for(auto event : events) {
                if(loc == event->getLocation()) {
                    result.push_back(event);
                } 
            }
            return result;
        }
};
class EventManager {
    private:
        std::vector<Event*> events;
        std::string notificationPreference;
    public:
        void displayMenu() {
            int choice;
            do {
                std::cout << "Manager\n";
                std::cout << "1. Create event\n";
                std::cout << "2. Search event\n";
                std::cout << "3. Display Event Details\n";
                std::cout << "4. List All Upcoming Events\n";
                std::cout << "5. RSVP for Event\n";
                std::cout << "6. Set Notification Preferences\n";
                std::cout << "7. Display Attendance\n";
                std::cout << "0. Exit\n";
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        createEvent();
                        break;
                    case 2:
                        searchEvents();
                        break;
                    case 3:
                        displaySearchResults(events);
                        break;
                    case 4:
                        listUpcomingEvents();
                        break;
                    case 5:
                        rsvpEvent();
                        break;
                    case 6:
                        setNotificationPreferences();
                        break;
                    case 7:
                        displayAttendance();
                        break;
                    case 0:
                        std::cout << "Exit manager";
                        break;
                    default:
                        std::cout << "Invalid choice. Try again.\n";
                }
                sendNotifications();
            } while(choice != 0);
        }
        void createEvent() {
            int eventType;
            std::cout << "Select event type:\n";
            std::cout << "1. Workshop\n";
            std::cout << "2. Concert\n";
            std::cout << "3. Conference\n";
            std::cin >> eventType;

            std::string name, date, location;
            std::cout << "Enter Event Name: ";
            std::cin.ignore(); 
            std::getline(std::cin, name);
            std::cout << "Enter Event Date (YYYY-MM-DD): ";
            std::cin >> date;
            std::cout << "Enter Location: ";
            std::cin >> location;

            if (eventType == 1) {
                std::string duration, instructor;
                std::cout << "Enter Duration: ";
                std::cin.ignore(); 
                std::getline(std::cin, duration);
                std::cout << "Enter Instructor: ";
                std::cin.ignore(); 
                std::getline(std::cin, instructor);
                WorkshopFactory workshopFactory;
                events.push_back(workshopFactory.createEvent(name, date, location, duration, instructor));
            } else if (eventType == 2) {
                std::string band, genre;
                std::cout << "Enter Band Name: ";
                std::cin.ignore(); 
                std::getline(std::cin, band);
                std::cout << "Enter Genre: ";
                std::cin.ignore(); 
                std::getline(std::cin, genre);
                ConcertFactory concertFactory;
                events.push_back(concertFactory.createEvent(name, date, location, band, genre));
            } else if (eventType == 3) {
                std::string speakers, topics;
                std::cout << "Enter Speakers: ";
                std::cin.ignore();
                std::getline(std::cin, speakers);
                std::cout << "Enter Topics: ";
                std::cin.ignore();
                std::getline(std::cin, topics);
                ConferenceFactory conferenceFactory;
                events.push_back(conferenceFactory.createEvent(name, date, location, speakers, topics));
            }else {
                std::cout << "Invalid choice.\n";
            }
        }
        void searchEvents() {
            int searchChoice;
            std::cout << "Select search by what\n";
            std::cout << "1. By type.\n";
            std::cout << "2. By date.\n";
            std::cout << "3. By location.\n";
            std::cin >> searchChoice;

            if (searchChoice == 1) {
                std::string type;
                std::cout << "Enter your type\n";
                std::cin.ignore(); 
                std::getline(std::cin, type);
                SearchType searchType;
                auto results = searchType.searchEvent(events, type);
                displaySearchResults(results);
            } else if (searchChoice == 2) {
                std::string date;
                std::cout << "Enter date (YYYY-MM-DD): \n";
                std::cin >> date;
                SearchDate searchDate;
                auto results = searchDate.searchEvent(events, date);
                displaySearchResults(results);
            } else if (searchChoice == 3) {
                std::string location;
                std::cout << "Enter location: \n";
                std::cin >> location;
                SearchLocation searchLocation;
                auto results = searchLocation.searchEvent(events, location);
                displaySearchResults(results);
            } else {
                std::cout << "Invalid choice.\n";
            }
        }
        void displaySearchResults(const std::vector<Event*>& results) {
            if (results.empty()) {
                std::cout << "No events found.\n";
            } else {
                for (auto event : results) {
                    std::cout << event->getDetails() << std::endl;
                }
            }
        }
        void listUpcomingEvents() {
            bool Upcoming = false;
            for (auto event : events) {
                if (event->isUpcoming()) {
                    std::cout << event->getDetails() << std::endl;
                    Upcoming = true;
                }   
            }
            if (!Upcoming) {
                std::cout << "No upcoming events found." << std::endl;
            }
        }
        void rsvpEvent() {
            std::string eventName, userName;
            std::cout << "Enter the event name you want to RSVP for: ";
            std::cin >> eventName;

            for (auto& event : events) {
                if (event->getEventName() == eventName) {
                    std::cout << "Enter your name for RSVP: ";
                    std::cin >> userName;
                    event->addRSVP(userName);
                    std::cout << "RSVP successful!\n";
                    return;
                }
            }
            std::cout << "Event not found.\n";
        }
        void displayAttendance() {
            std::string eventName;
            std::cout << "Please enter your even name:";
            std::cin.ignore();
            std::getline(std::cin, eventName);
            for (auto& event : events) {
                if (event->getEventName() == eventName) { 
                    std::cout << "Attendance for event: " << eventName << "\n";
                    std::cout << "Total attendees: " << event->getRSVPCount() << "\n";
                    std::cout << "Attendee List:\n";

                    const auto& rsvpList = event->getRSVPList();
                    for (const auto& attendee : rsvpList) {
                        std::cout << "- " << attendee << "\n"; 
                    }
                    return; 
                }
            }
            std::cout << "Event not found: " << eventName << "\n"; 
        }
        void setNotificationPreferences() {
            int choice;
            std::cout << "Set notification preference:\n";
            std::cout << "1. Daily notifications\n";
            std::cout << "2. Weekly notifications\n";
            std::cin >> choice;

            if (choice == 1) {
                notificationPreference = "daily";
                std::cout << "Daily notifications set.\n";
            } else if (choice == 2) {
                notificationPreference = "weekly";
                std::cout << "Weekly notifications set.\n";
            } else {
                std::cout << "Invalid choice.\n";
            }
        }
        void sendNotifications() {
        auto today = date::floor<date::days>(std::chrono::system_clock::now());
        std::cout << "Today: " << date::format("%F", today) << "\n";

        for (auto& event : events) {
            date::sys_days eventDate;
            std::istringstream in{event->getEventDate()};

            // Error handling for date parsing
            if (!(in >> date::parse("%F", eventDate))) {
                std::cout << "Failed to parse event date: " << event->getEventDate() << "\n";
                continue; // Skip this event if parsing fails
            }

            // Convert sys_days to system_clock::time_point
            auto eventTimePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(eventDate);
            auto duration = eventTimePoint - today; // Calculate duration from today to the event date

            // Check for daily notifications
            if (notificationPreference == "daily" && event->isUpcoming()) {
                // Calculate remaining days
                auto remainingDays = std::chrono::duration_cast<std::chrono::seconds>(duration).count() / (60 * 60 * 24); // Convert to days
                std::cout << "Remain " << remainingDays << " days for event: " << event->getEventName() << "\n";
            } 
            // Check for weekly notifications
            else if (notificationPreference == "weekly" && event->isUpcoming() && 
                     std::chrono::duration_cast<std::chrono::seconds>(duration).count() % (60 * 60 * 24 * 7) == 0) {
                auto remainingWeeks = std::chrono::duration_cast<std::chrono::seconds>(duration).count() / (60 * 60 * 24 * 7);
                std::cout << "Upcoming event: " << event->getEventName() << " within " << remainingWeeks << " weeks.\n";
            }  
        }
    }
        ~EventManager() {
            for (auto event : events) {
                delete event; 
            }
        }

    
};
int main() {
    EventManager manager;
    manager.displayMenu();
    return 0;
}