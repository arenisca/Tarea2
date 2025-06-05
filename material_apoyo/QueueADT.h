#ifndef QUEUEADT
#define QUEUEADT

class QueueADT{

    public:
        virtual void enqueue(int) = 0;
        virtual void dequeue() = 0;
        virtual int front() = 0;
        virtual bool is_empty() = 0;
        virtual int size() = 0; 
};

#endif