#include <stdlib.h>

int can_complete_circuit(int* gas, int gas_size, int* cost, int cost_size) {
    int total_tank = 0, current_tank = 0, start_index = 0;
    
    for (int i = 0; i < gas_size; i++) {
        int balance = gas[i] - cost[i];
        total_tank += balance;
        current_tank += balance;
        
        if (current_tank < 0) {
            start_index = i + 1;
            current_tank = 0;
        }
    }
    
    return (total_tank >= 0) ? start_index : -1;
}
