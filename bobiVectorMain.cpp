#include <iostream>
#include <typeinfo>
#include <string>

#define quote(x) #x

using namespace std;



class MyObject{
    string str;
public:
    MyObject(string name){
        str = name;
        print();
        cout << "constructor" << endl;
    }

    MyObject (const MyObject& other){
        str = other.str;
        print();
        cout << "copy constructor" << endl;
    }

    MyObject& operator=(const MyObject& other){
        print();
        cout << "operator=" << endl;

        return *this;
    }

    ~MyObject(){
        print();
        cout << "destructor" << endl;
    }

    string getName() const {
        return str;
    }


private:
    void print() const {
        //cout << typeid(*this).name() << " ";

        cout <<str << " ";
    }

};


template <class T>
class myVector{
public:

    myVector(){
        //myVector(10); //don't use this
        capacity = 10;
        size_ = 0;

        data = static_cast<T*> (operator new(capacity*sizeof(T)));
    }

    myVector(long cap){
        capacity = cap;
        size_ = 0;

        //cout << size_ << endl;
        //data = new T[capacity];
        data = static_cast<T*> (operator new(capacity*sizeof(T)));
    }

    ~myVector(){
        //delete [] data; //this one make millions of destructor calls even if it's just a capacity of 10

        for(int i = 0; i < size_; i++){
            data[i].~T();
        }
        operator delete(data); // don't know if it works
    }

    void pushBack(const T& elem){
        if(isFull()){
            myResize();
        }

        new (data + size_) T(elem);
        size_++;
    }

    void popBack() {
        if(!isEmpty()){
            size_ --;
            data[size_].~T();
        }
    }

    T& vectBack() {
        if(!isEmpty()){
            return data[size_-1];
        }
        else{
            //unknown behavior
            return data[size_];
        }
    }

    T& operator[](long n){
        if(n<size_ && n>=0){
            return data[n];
        }
        else {
            //unknown behavior
            return data[0];
        }

    }



    bool isEmpty() const {
        //cout << size_ << endl;
        return vectSize() == 0;
    }

    long vectSize() const {
        return size_;
    }

    /*void operator delete[](void* mem){   // it is a static function
        //cout << "hello" << endl;
        for(long i = 0; i< size_;i++){
            data[i].~T();

        }
        delete data;
    }*/

private:
    long capacity;
    long size_;
    T* data;

    bool isFull() const {
        return size_ == capacity;
    }

    void myResize(){
        cout << "my name is Resize" << endl;

        capacity*=2;
        T* temp = static_cast<T*> (operator new(capacity*sizeof(T)));

        for(int i = 0; i< size_; i++){
            new (temp + i) T(data[i]);
            data[i].~T();
        }

        operator delete(data);
        data = temp;
    }
};


 ostream& operator<<(std::ostream& os, const MyObject& obj){
    os<<obj.getName();
    return os;
}

int main()
{
    MyObject obj("bobi");
    MyObject obj2("pesho");
    MyObject obj3("gosho");

    cout <<"------------------------------------" << endl;

    //cout << obj;
    //::operator delete[](&obj);
    /*myVector<int> vect;


    vect.pushBack(3);
    vect.pushBack(5);/* */

    myVector<MyObject> testObjVector(2);

    testObjVector.pushBack(obj);
    testObjVector.pushBack(obj2);

    cout <<"------------------------------------" << endl;
    //testObjVector.popBack();

    testObjVector.pushBack(obj3);


    cout << "hello "<<testObjVector[1] << endl;

    cout << "yo " << testObjVector.vectBack() << endl;

    //cout << vect.isEmpty() << " " << vect.vectSize() << endl;
    //obj2 = obj;

    return 0;
}
