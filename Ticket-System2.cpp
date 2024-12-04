#include <iostream>
#include <queue>
#include <string>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <mutex>
#include <condition_variable>

class Person {
public:
    std::string name;
    int ticket_number;

    Person(std::string name, int ticket_number) : name(name), ticket_number(ticket_number) {}
};

class Queue {
private:
    std::queue<Person> q;
    int next_ticket_number = 1;
    std::unordered_map<std::string, int> name_to_position;
    std::unordered_map<int, int> ticket_to_position;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void Enqueue(const std::string& name) {
        std::lock_guard<std::mutex> lock(mtx);
        Person person(name, next_ticket_number);
        q.push(person);
        name_to_position[name] = q.size();
        ticket_to_position[next_ticket_number] = q.size();
        std::cout << name << " added to the queue with Ticket #" << next_ticket_number << std::endl;
        next_ticket_number++;
    }

    void AutoDequeue() {
        auto last_dequeue_time = std::chrono::steady_clock::now();
        
        while (true) {
            auto current_time = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed = current_time - last_dequeue_time;
            
            if (elapsed.count() >= 60.0) {  
                Dequeue();
                last_dequeue_time = current_time;

                cv.notify_one();
            }
            std::this_thread::sleep_for(std::chrono::seconds(1)); 
        }
    }

    void Dequeue() {
        std::lock_guard<std::mutex> lock(mtx);
        
        if (q.empty()) {
            std::cout << "Queue is empty. No one to dequeue." << std::endl;
            return;
        }

        std::cout << "\nAfter 1 minute..." << std::endl;

        Person person = q.front();
        q.pop();
        std::cout << "Dequeue: " << person.name << " received a ticket (Ticket #" << person.ticket_number << ")" << std::endl;

        std::cout << "Queue size: " << q.size() << std::endl;

        if (!q.empty()) {
            Person next_person = q.front();
            std::cout << "Next in line: " << next_person.name << " (Ticket #" << next_person.ticket_number << ")" << std::endl;
        } else {
            std::cout << "No one is next in line. The queue is empty." << std::endl;
        }

        name_to_position.erase(person.name);
        ticket_to_position.erase(person.ticket_number);
        UpdatePositions();
    }

    void UpdatePositions() {
        std::queue<Person> temp = q;
        int pos = 1;
        name_to_position.clear();
        ticket_to_position.clear();
        
        while (!temp.empty()) {
            Person person = temp.front();
            temp.pop();
            name_to_position[person.name] = pos;
            ticket_to_position[person.ticket_number] = pos;
            pos++;
        }
    }

    bool IsEmpty() const {
        return q.empty();
    }

    int Size() const {
        return q.size();
    }

    void Peek() const {
        if (!q.empty()) {
            const Person& person = q.front();
            std::cout << "Next in line: " << person.name << " (Ticket #" << person.ticket_number << ")" << std::endl;
        } else {
            std::cout << "Queue is empty." << std::endl;
        }
    }

    void Position(const std::string& identifier) const {
        if (name_to_position.find(identifier) != name_to_position.end()) {
            std::cout << identifier << " is currently at position " << name_to_position.at(identifier) << " in the queue." << std::endl;
        } else {
            try {
                int ticket_num = std::stoi(identifier);
                if (ticket_to_position.find(ticket_num) != ticket_to_position.end()) {
                    std::cout << "Ticket #" << ticket_num << " is currently at position " << ticket_to_position.at(ticket_num) << " in the queue." << std::endl;
                } else {
                    std::cout << "Ticket number or name not found in the queue." << std::endl;
                }
            } catch (...) {
                std::cout << "Invalid input. Enter a valid name or ticket number." << std::endl;
            }
        }
    }

    void WaitForAutoDequeue() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::seconds(1));  
    }
};

int main() {
    Queue concertQueue;
    int option;
    std::string input;

    std::cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!" << std::endl;
    std::cout << "1. Enqueue a person\n2. Check your position in the queue\n3. Exit" << std::endl;

    std::thread dequeue_thread(&Queue::AutoDequeue, &concertQueue);
    dequeue_thread.detach();

    while (true) {
        concertQueue.WaitForAutoDequeue();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "\nChoose an option: ";
        std::cin >> option;
        std::cin.ignore();  

        if (option == 1) {
            std::cout << "Enter the name: ";
            std::getline(std::cin, input);
            concertQueue.Enqueue(input);
            std::cout << "Queue size: " << concertQueue.Size() << std::endl;
        } else if (option == 2) {
            std::cout << "Enter your name or ticket number: ";
            std::getline(std::cin, input);
            concertQueue.Position(input);
        } else if (option == 3) {
            std::cout << "Exiting system." << std::endl;
            break;
        } else {
            std::cout << "Invalid option. Please choose again." << std::endl;
        }
    }

    return 0;
}
