//-----------------------------------------------------------------------------
// List.cpp
// Implementation of the List ADT
// Bradley Haire
// bhaire
// pa6
//-----------------------------------------------------------------------------


#include "List.h"
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

#include <climits>
static const int INF = INT_MIN;

List::Node::Node(ListElement e) {
    data = e;
    next = nullptr;
    prev = nullptr;
}

List::List() {
    frontDummy = new Node(INF);
    backDummy = new Node(INF);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;
}

List::List(const List& l) {
    this->frontDummy = new Node(INF);
    this->backDummy = new Node(INF);
    this->afterCursor = this->backDummy;
    this->beforeCursor = this->frontDummy;
    this->backDummy->prev = this->frontDummy;
    this->frontDummy->next = this->backDummy;
    this->num_elements = 0;
    this->pos_cursor = 0;

    Node* node = l.frontDummy->next;
    if (l.length() != 0 ) {
        do {
            if (node == l.backDummy) {
                break;
            }
            int val = node->data;
            this->insertAfter(val);
            this->moveNext();
            node = node->next;
        }
        while(node->data != INF);
    }

}

List::~List() {
    this->moveFront();
    while(this->num_elements > 0) {
        this->eraseAfter();
    }
    delete this->frontDummy;
    delete this->backDummy;
}

int List::length() const {
    return this->num_elements;
}

ListElement List::front() const {
    if (this->num_elements == 0) {
        throw std::length_error("List: front(): empty List");
    }
    return this->frontDummy->next->data;
}

ListElement List::back() const {
    if (this->num_elements == 0) {
        throw std::length_error("List: back(): empty List");
    }
    return this->backDummy->prev->data;
}

int List::position() const {
    return this->pos_cursor;
}


ListElement List::peekNext() const {
    if (this->num_elements == this->pos_cursor) {
        throw std::domain_error("List: peekNext(): cursor is at the end of the list");
    }
    return this->afterCursor->data;
    
}

ListElement List::peekPrev() const {
    if (0 == this->pos_cursor) {
        throw std::domain_error("List: peekPrev(): cursor is at the beginning of the list");
    }
    return this->beforeCursor->data;
}

void List::clear() {
    this->moveFront();
    while(this->num_elements > 0) {
        this->eraseAfter();
    }
}

void List::moveFront() {
    this->pos_cursor = 0;
    this->beforeCursor = this->frontDummy;
    this->afterCursor = this->frontDummy->next;
}

void List::moveBack() {
    this->pos_cursor = this->num_elements;
    this->beforeCursor = this->backDummy->prev;
    this->afterCursor = this->backDummy;
}

ListElement List::moveNext() {
    if (this->num_elements == this->pos_cursor) {
        throw std::domain_error("List: moveNext(): cursor is at the end of the list");
    }
    this->pos_cursor += 1;
    this->beforeCursor = this->beforeCursor->next;
    this->afterCursor = this->afterCursor->next;
    return this->beforeCursor->data;
}

ListElement List::movePrev() {
    if (0 == this->pos_cursor) {
        throw std::domain_error("List: movePrev(): cursor is at the beginning of the list");
    }
    this->pos_cursor -= 1;
    this->beforeCursor = this->beforeCursor->prev;
    this->afterCursor = this->afterCursor->prev;
    return this->afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* n = new Node(x);
    n->next = this->afterCursor;
    n->prev = this->beforeCursor;
    this->beforeCursor->next = n;
    this->afterCursor->prev = n;
    this->afterCursor = n;
    this->num_elements += 1;
}

void List::insertBefore(ListElement x) {
    Node* n = new Node(x);
    n->next = this->afterCursor;
    n->prev = this->beforeCursor;
    this->beforeCursor->next = n;
    this->afterCursor->prev = n;
    this->beforeCursor = n;
    this->num_elements += 1;
    this->pos_cursor += 1;
}

void List::setAfter(ListElement x) {
    if (this->num_elements == this->pos_cursor) {
        throw std::domain_error("List: setAfter(): cursor is at the end of the list");
    }
    this->afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (0 == this->pos_cursor) {
        throw std::domain_error("List: setBefore(): cursor is at the beginning of the list");
    }
    this->beforeCursor->data = x;
}

void List::eraseAfter() {
    if (this->num_elements <= this->pos_cursor) {
        throw std::domain_error("List: eraseAfter(): cursor is at the end of the list");
    }
    Node* to_delete = this->afterCursor;
    this->beforeCursor->next = this->beforeCursor->next->next;
    this->beforeCursor->next->prev = this->beforeCursor;
    this->afterCursor = this->beforeCursor->next;
    this->num_elements -= 1;
    delete to_delete;
}

void List::eraseBefore() {
    if (0 == this->pos_cursor) {
        throw std::domain_error("List: eraseBefore(): cursor is at the beginning of the list");
    }
    Node* to_delete = this->beforeCursor;
    this->afterCursor->prev = this->afterCursor->prev->prev;
    this->afterCursor->prev->next = this->afterCursor;
    delete to_delete;
    this->beforeCursor = this->afterCursor->prev;
    this->num_elements -= 1;
    this->pos_cursor -= 1;
}

int List::findNext(ListElement x) {
    Node* cur = this->afterCursor;
    while (cur != nullptr) {
        this->pos_cursor += 1;
        if(cur->data == x) {
            this->afterCursor = cur->next;
            this->beforeCursor = cur;
            return this->pos_cursor;
        }
        cur = cur->next;
    }
    this->afterCursor = this->backDummy;
    this->beforeCursor = this->backDummy->prev;
    this->pos_cursor = this->num_elements;
    return -1;
}

int List::findPrev(ListElement x) {
    Node* cur = this->beforeCursor;
    while (cur != nullptr) {
        this->pos_cursor -= 1;
        if(cur->data == x) {
            this->beforeCursor = cur->prev;
            this->afterCursor = cur;
            return this->pos_cursor;
        }
        cur = cur->prev;
    }
    this->afterCursor = this->frontDummy->next;
    this->beforeCursor = this->frontDummy;
    this->pos_cursor = 0;
    return -1;
}

void List::cleanup() {
    int temp_position = 0;
    Node* cur = this->frontDummy->next;
    ListElement x = INF;
    // this is our start, and our cursor starts behind the element
    bool hit_cursor = false;
    bool got_val = false;
    
    int numbers_seen [this->num_elements];
    int values_inserted = 0;
    while(cur->next != nullptr) {
        if (!hit_cursor && temp_position == this->pos_cursor) {
            hit_cursor = true;
        }
        int value = cur->data;
        bool deleted_element = false;
        for (int i = 0; i < values_inserted; i += 1) {
            if (value == numbers_seen[i]) {
                // then it is already seen before and must be removed
                Node* to_delete = cur;
                cur = cur->next;
                to_delete->prev->next = cur;
                cur->prev = to_delete->prev;
                delete to_delete;
                deleted_element = true;
                this->num_elements -= 1;
                break;
            }
        }
        if(!deleted_element) {
            // then this is an element we have not seen before
            numbers_seen[values_inserted] = value;
            values_inserted += 1;
            cur = cur->next;
            if(hit_cursor && !got_val) {
                x = value;
                got_val = true;
            }
        }
        temp_position += 1;
    }
    if(x != INF) {
        this->moveFront();
        if(this->findNext(x) != -1) {  
            this->movePrev();
        }

    }
    if (!hit_cursor) {
        this->moveBack();
    }
   
}

List List::concat(const List& l) const {
    List list;
    if (this->num_elements != 0) {
        Node* cur = this->frontDummy->next;
        while(cur->data != INF) {
            list.insertAfter(cur->data);
            list.moveNext();
            cur = cur->next;
        }
    }
    if(l.length() != 0) {
        Node * cur = l.frontDummy->next;
        while(cur->data != INF) {
            list.insertAfter(cur->data);
            list.moveNext();
            cur = cur->next;
        }
    }
    list.pos_cursor = 0;
    list.beforeCursor = list.frontDummy;
    list.afterCursor = list.frontDummy->next;
    return list;
}

std::string List::to_string() const {
    if (this->num_elements == 0) {
        return "()";
    }
    Node* cur = this->frontDummy->next;
    std::string repr = "(";
    if (this->num_elements != 0) {
        repr += std::to_string(cur->data);
        cur = cur->next;
    }
    
    while(cur->data != INF) {
        repr += ",";
        repr += std::to_string(cur->data);
        cur = cur->next;
    }
    repr += ")";
    return repr;
}

bool List::equals(const List& l) const {
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = ( this->num_elements == l.num_elements);
    N = this->frontDummy->next;
    M = l.frontDummy->next;
    while (eq && N->data != INT_MIN) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

std::ostream& operator<<( std::ostream& stream, const List& l ) {
    stream << l.to_string() << endl;
    return stream;
}

bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

List& List::operator=(const List& l) {
    if ( this != &l) {
        List tmp = l;
        std::swap(this->frontDummy, tmp.frontDummy);
        std::swap(this->backDummy, tmp.backDummy);
        std::swap(this->num_elements, tmp.num_elements);
    }
    return *this;
}



