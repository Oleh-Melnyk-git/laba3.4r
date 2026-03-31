#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *next;
  Node(int val) : data(val), next(nullptr) {}
};

// Додавання елемента в кінець кільцевого списку
void addBack(Node *&head, int value) {
  Node *newNode = new Node(value);
  if (!head) {
    head = newNode;
    head->next = head; // кільце
  } else {
    Node *temp = head;
    while (temp->next != head) {
      temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
  }
}

// Рекурсивне дублювання елементів із заданим значенням
void duplicateRecursive(Node *current, Node *head, int target) {
  if (!current)
    return;
  // Якщо ми повернулися до початку — завершуємо
  if (current->next == head) {
    if (current->data == target) {
      Node *newNode = new Node(target);
      newNode->next = head;
      current->next = newNode;
    }
    return;
  }

  // Якщо поточний елемент має потрібне значення — дублюємо
  if (current->data == target) {
    Node *newNode = new Node(target);
    newNode->next = current->next;
    current->next = newNode;
    duplicateRecursive(newNode->next, head, target); // пропускаємо дубль
  } else {
    duplicateRecursive(current->next, head, target);
  }
}

// Виведення списку
void printList(Node *head) {
  if (!head)
    return;
  Node *temp = head;
  do {
    cout << temp->data << " ";
    temp = temp->next;
  } while (temp != head);
  cout << endl;
}

// Видалення списку
void deleteList(Node *&head) {
  if (!head)
    return;
  Node *temp = head->next;
  while (temp != head) {
    Node *nextNode = temp->next;
    delete temp;
    temp = nextNode;
  }
  delete head;
  head = nullptr;
}

int main() {
  Node *head = nullptr;
  addBack(head, 5);
  addBack(head, 7);
  addBack(head, 3);
  addBack(head, 7);

  cout << "Початковий список: ";
  printList(head);

  int target = 5;
  duplicateRecursive(head, head, target);

  cout << "Після рекурсивного дублювання (" << target << "): ";
  printList(head);

  deleteList(head);
  return 0;
}
