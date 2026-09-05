#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct one_result{
    unsigned char score_1;
    unsigned char score_2;
};

void askForNumberOfCommands(unsigned int* number_of_teams_p);
void askForValues(one_result* results_p, unsigned int number_of_teams);
void printResults(one_result* results_p, unsigned int number_of_teams);

int main(){

    unsigned int number_of_teams = 0;

    askForNumberOfCommands(&number_of_teams);

    one_result* results_p =  (one_result*) calloc(((number_of_teams - 1) * number_of_teams) / 2, sizeof(one_result));// Ровно под количество матчей

    askForValues(results_p, number_of_teams);

    printResults(results_p, number_of_teams);

}

void askForNumberOfCommands(unsigned int* number_of_teams_p){

    assert(number_of_teams_p);

    printf("How many teams will be playing football? ");
    scanf("%d", number_of_teams_p);
}

void askForValues(one_result* results_p, unsigned int number_of_teams){

    assert(results_p);
    assert(number_of_teams > 1);

    for(unsigned int first_team = 2; first_team <= number_of_teams; first_team++){//first_team и second_team - номера команд, начинающихся с 1

        for(unsigned int second_team = 1; second_team < first_team; second_team++){

            printf("\nEnter the math results for the match of  %u team and %u team, the score of %u team: ", first_team, second_team, first_team);

            scanf("%hhu", &((results_p + (((first_team - 1) * (first_team - 2)) / 2) + (second_team - 1))->score_1));

            printf("\nThe score of %u team: ", second_team);

            scanf("%hhu", &((results_p + (((first_team - 1) * (first_team - 2)) / 2) + (second_team - 1))->score_2));
        }
    }

}

void printResults(one_result* results_p, unsigned int number_of_teams){

    assert(results_p);
    assert(number_of_teams > 1);

    unsigned char score_1 = 0;
    unsigned char score_2 = 0;

    printf("\nFirst/Second ");

    for(unsigned int team = 1; team < number_of_teams; team++){
        printf("%d      ", team);
    }
    printf("\n");

    for(unsigned int first_team = 2; first_team <= number_of_teams; first_team++){//first_team и second_team - номера команд, начинающихся с 1

        printf("%d            ", first_team);
        for(unsigned int second_team = 1; second_team < first_team; second_team++){

            score_1 = ((results_p + (((first_team - 1) * (first_team - 2)) / 2) + (second_team - 1))->score_1);
            score_2 = ((results_p + (((first_team - 1) * (first_team - 2)) / 2) + (second_team - 1))->score_2);

            printf("%u %u   ", score_1, score_2);
        }
        printf("\n");
    }
}

//changes
//new changes
