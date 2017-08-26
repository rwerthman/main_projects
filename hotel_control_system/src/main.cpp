//
//  main.cpp
//  HotelControlSystem
//

/*
  Create mulitple instances so mulitple people can ask for elevators at the same time
  probably with sockets

  Store both the destinatoin floor and the direction the person requested in the
  destinatino floor queue for each elevator

*/

#include "HotelControlSystem.h"
#include <iostream>
#include <thread>


// Simple testing function to check the code logic
void assert(int test, std::string msg) {
    if (!test) {
        printf("FAILED: %s \n", msg.c_str());
    } else {
        printf("PASSED: %s \n", msg.c_str());
    }
}

// void test_dispatch_elevator_to_floor() {
//     /*
//     Elevator 1 is stopped on the 5th floor heading up with requests for
//     floors 10, 12 and 18.   Elevator two is heading down, moving, at the 14th floor, with a stop at 2
//     and the lobby.   Elevator 3 is heading up, moving  with a stop at the 15th floor.
//     Someone pushed the down button on the 13th floor.
//      */
//     std::queue<Request*> *shared_queue = new std::queue<Request*>;
//     HotelControlSystem h = HotelControlSystem();
//     h.initialize_members(shared_queue);
//
//     Floor* floors = h.get_floors();
//     Elevator* elevators = h.get_elevators();
//
//     elevators[0].add_floor_to_destination_floors_queue(10);
//     elevators[0].add_floor_to_destination_floors_queue(12);
//     elevators[0].add_floor_to_destination_floors_queue(18);
//     elevators[0].set_current_floor(5);
//     elevators[0].determine_direction_of_travel();
//
//     elevators[1].set_current_floor(14);
//     elevators[1].add_floor_to_destination_floors_queue(2);
//     elevators[1].add_floor_to_destination_floors_queue(0);
//     elevators[1].determine_direction_of_travel();
//
//     elevators[2].set_current_floor(0);
//     elevators[2].add_floor_to_destination_floors_queue(15);
//     elevators[2].determine_direction_of_travel();
//
//     h.display_current_elevator_information();
//
//     h.press_elevator_button_from_floor(floors[12], "down");
//     h.press_elevator_button_from_floor(floors[0], "up");
//
//     assert(elevators[1].destination_floors_queue_size() == 3, "Elevator 1 has 3 floors to go to.");
//     assert(elevators[2].destination_floors_queue_size() == 2, "Elevator 2 has 2 floors to go to.");
//
//     delete shared_queue;
// }
//
// void test_shared_queue() {
//     std::queue<Request*> *shared_queue = new std::queue<Request*>;
//
//     HotelControlSystem h = HotelControlSystem();
//     h.initialize_members(shared_queue);
//
//     Elevator* elevators = h.get_elevators();
//
//     Request *r = new Request(2, "up");
//     elevators[0].add_request_to_queue(r);
//     r = new Request(3, "down");
//     elevators[2].add_request_to_queue(r);
//
//     r = h.get_request_from_queue();
//
//     assert(r->get_floor() == 2, "Hotel Control System removed request for floor 2.");
//     assert(r->get_direction() == "up", "Hotel Control System remove request for up direction.");
//     assert(h.get_request_queue_size() == 1, "Hotel Control System queue is the right size.");
//
//     delete r;
//     delete shared_queue;
// }
//
// void test_advance_to_next_step() {
//     std::queue<Request*> *shared_queue = new std::queue<Request*>;
//     HotelControlSystem h = HotelControlSystem();
//     h.initialize_members(shared_queue);
//
//     Floor* floors = h.get_floors();
//     Elevator* elevators = h.get_elevators();
//
//     elevators[0].add_floor_to_destination_floors_queue(10);
//     elevators[0].add_floor_to_destination_floors_queue(12);
//     elevators[0].add_floor_to_destination_floors_queue(18);
//     elevators[0].set_current_floor(5);
//     elevators[0].determine_direction_of_travel();
//
//     elevators[1].set_current_floor(14);
//     elevators[1].add_floor_to_destination_floors_queue(2);
//     elevators[1].add_floor_to_destination_floors_queue(0);
//     elevators[1].determine_direction_of_travel();
//
//     elevators[2].set_current_floor(1);
//     elevators[2].determine_direction_of_travel();
//
//     h.display_current_elevator_information();
//
//     h.press_elevator_button_from_floor(floors[12], "down");
//     h.press_elevator_button_from_floor(floors[0], "up");
//
//     elevators[0].advance_to_next_step();
//     elevators[1].advance_to_next_step();
//
//     elevators[2].advance_to_next_step();
//     elevators[2].advance_to_next_step();
//
//     assert(elevators[0].get_current_floor() == 6, "Elevator 0 moved the right floor.");
//     assert(elevators[0].get_direction_of_travel() == "up", "Elevator 0 is traveling in the right direction.");
//
//     assert(elevators[1].get_current_floor() == 13, "Elevator 1 moved the right floor.");
//     assert(elevators[1].get_direction_of_travel() == "down", "Elevator 1 is traveling in the right direction.");
//
//     assert(elevators[2].get_current_floor() == 0, "Elevator did not move.");
//     assert(elevators[2].get_direction_of_travel() == "stopped", "Elevator 1 is traveling in the right direction.");
//     assert(elevators[2].destination_floors_queue_size() == 0, "Elevator 1 has no destination floors.");
//     assert(shared_queue->size() == 1, "Request queue has the correct size.");
//
//     Request *r = h.get_request_from_queue();
//
//     assert(r->get_floor() == 0, "Hotel Control System removed request for floor 0.");
//     assert(r->get_direction() == "down", "Hotel Control System remove request for up direction.");
//
//     delete shared_queue;
// }

void test_multi_threading() {
    std::queue<Request*> *shared_queue = new std::queue<Request*>;
    std::mutex *request_queue_mutex = new std::mutex;
    HotelControlSystem h = HotelControlSystem();
    h.initialize_members(shared_queue, request_queue_mutex);

    Elevator* elevators = h.get_elevators();
    Floor* floors = h.get_floors();

    elevators[0].add_request_to_destination_floors_queue(new Request(10, "up"));
    elevators[0].add_request_to_destination_floors_queue(new Request(12, "up"));
    elevators[0].add_request_to_destination_floors_queue(new Request(18, "down"));
    elevators[0].set_current_floor(5);
    elevators[0].determine_direction_of_travel();

    elevators[1].set_current_floor(14);
    elevators[1].add_request_to_destination_floors_queue(new Request(2, "up"));
    elevators[1].add_request_to_destination_floors_queue(new Request(0, "up"));
    elevators[1].determine_direction_of_travel();

    elevators[2].set_current_floor(0);
    elevators[2].add_request_to_destination_floors_queue(new Request(15, "down"));
    elevators[2].determine_direction_of_travel();

    h.display_current_elevator_information();

    h.press_elevator_button_from_floor(floors[12], "down");
    h.press_elevator_button_from_floor(floors[6], "up");

    // Assign a thread to each elevator
    std::thread t1(&Elevator::advance_to_next_step, &elevators[0]);
    std::thread t2(&Elevator::advance_to_next_step, &elevators[1]);
    std::thread t3(&Elevator::advance_to_next_step, &elevators[2]);
    std::thread t4(&HotelControlSystem::manage_request_queue, &h);

    int floor, elevator;
    std::string direction;

    while (true) {
        std::cout << "Please enter your current floor (0 - 20): " << std::endl;
        std::cin >> floor;
        std::cout << "Please enter a direction you would like to go (up or down): " << std::endl;
        std::cin >> direction;
        elevator = h.press_elevator_button_from_floor(floors[floor], direction);

        // Figure out how to the elevator that arrived at the floor
        printf("Elevator %d has been sent to your floor...\n", elevator);
        std::cout << "Please enter the floor you would like to go to: " << std::endl;
        std::cin >> floor;
        h.press_floor_button_from_elevator(elevators[elevator], floor);
    }

    t1.join();
    t2.join();
    t3.join();

    h.display_current_elevator_information();
}

int main(int argc, const char * argv[]) {
    // test_dispatch_elevator_to_floor();
    // test_shared_queue();
    // test_advance_to_next_step();
    test_multi_threading();
    return 0;
}
