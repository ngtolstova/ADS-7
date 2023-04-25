// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
struct SYM {
  char c;
  int prior;
} Elem;
template <typename T>
class TPQueue {
  private:
    struct PTR {
      struct PTR* frv;
      struct PTR* back;
      struct SYM* data;
    }
    int len;
    PTR* head;
    PTR* tail;
  
  public:
    TPQueue() {
      len = 0;
    }
    void push(T unt) {
      PTR* newptr = new PTR;
      SYM* newsym = new T;
      *newsym = unt;
      newptr->data = newsym;
      int i = 0;
      if (len == 0) {
        newptr->frv = NULL;
        newptr->back = NULL;
        head = newptr;
        tail = newptr;
        len = 1;
        return;
      }
      PTR* bufptr = head;
      for (i = 0; i < len; i++) {
        if (newptr->data->prior > bufptr->data->prior) {
          if (i == 0) {
            newptr->frv = bufptr;
            bufptr->back = newptr;
            head = newptr;
            len++;
            return;
          }
          bufptr->back->frv = newptr;
          newptr->back = bufptr->back;
          newptr->frv = bufptr;
          bufptr->back = newptr;
          len++;
          return;
        } else {
          bufptr = bufptr->frv;
        }
      }
      if (i == len) {
        tail->frv = newptr;
        newptr->back = tail;
        tail = newptr;
        len++;
      }
      return;
    }
    T pop() {
      if (len == 0) {
        return Elem;
      }
      PTR  bufptr = *head;
      PTR* del = head;
      len--;
      head = head->frv;
      head->back = NULL;
      SYM bufdata = *del->data;
      delete del->data;
      delete del;
      return bufdata;
    }
    void Vyvod() {
      PTR* buf = head;
      for (int i = 0; i < len; i++) {
        buf = buf->frv;
      }
      return;
    }
    ~TPQueue() {
      PTR* buf = head;
      PTR* del;
      for (int i = 0; i < len; i++) {
        del = buf;
        buf = buf->frv;
        delete del->data;
        delete del;
      }
    }
};

#endif  // INCLUDE_TPQUEUE_H_
