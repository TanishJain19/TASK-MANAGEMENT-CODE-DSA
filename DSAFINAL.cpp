#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a task node
typedef struct Task {
    char name[100];
    struct Task *prev;
    struct Task *next;
} Task;

// Function to create a new task node
Task* createTask(char name[]) {
    Task *newTask = (Task*)malloc(sizeof(Task));
    strcpy(newTask->name, name);
    newTask->prev = NULL;
    newTask->next = NULL;
    return newTask;
}

// Function to add a task to the end of the list
void addTask(Task **head, char name[]) {
    Task *newTask = createTask(name);
    if (*head == NULL) {
        *head = newTask;
    } else {
        Task *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTask;
        newTask->prev = current;
    }
}

// Function to remove a task from the list
void removeTask(Task **head, char name[]) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Task *current = *head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            printf("Task '%s' removed successfully.\n", name);
            return;
        }
        current = current->next;
    }
    printf("Task '%s' not found.\n", name);
}

// Function to display all tasks in the list
void displayTasks(Task *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Tasks:\n");
    while (head != NULL) {
        printf("%s\n", head->name);
        head = head->next;
    }
}

int main() {
    Task *head = NULL;
    int choice;
    char taskName[100];

    do {
        printf("\nTask Management Application\n");
        printf("1. Add Task\n");
        printf("2. Remove Task\n");
        printf("3. View Tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter task name: ");
                scanf("%s", taskName);
                addTask(&head, taskName);
                break;
            case 2:
                printf("Enter task name to remove: ");
                scanf("%s", taskName);
                removeTask(&head, taskName);
                break;
            case 3:
                displayTasks(head);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);

    return 0;
}

