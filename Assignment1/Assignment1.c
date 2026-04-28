#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 10
typedef struct {
    char buffer[SIZE];
    int head; //مؤشر الكتابة
    int tail; //مؤشر القراءة
    int count; //عدد العناصر الحالية
}
 CircularBuffer; //دالة التهيئة
void init(CircularBuffer *cb) {
    cb->head = 0; //ضبط مؤشر الكتابة عند الصفر في البداية
    cb->tail = 0; //ضبط مؤشر القراءة عند الصفر 
    cb->count = 0; //المخزن يبدأ ب 0 عنصر
}
bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
} //ممتلئ اذا تساوى العداد مع الحجم

bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
} //فارغ اذا كان العداد يساوي الصفر

// دالة الكتابة (الإدخال)
void write(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\n The buffer is full! [overflow] %c", data);
        return;
    }
    cb->buffer[cb->head] = data; // وضع الحرف في المكان الحالي للرأس
    cb->head = (cb->head + 1) % SIZE; // تحريك الرأس دائريا باستخدام باقي القسمة
    cb->count++; //زيادة عدد العناصر المخزنة
}

// دالة القراءة (الإزالة)
char read(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\n The buffer is empty! [underflow]");
        return '\0';
    }
    char data = cb->buffer[cb->tail]; //اخذ الحرف من مكان الذيل
    cb->tail = (cb->tail + 1) % SIZE; // تحريك الذيل دائريا
    cb->count--; //تقليل عدد العناصر
    return data;
}
int main() {
    CircularBuffer cb;
    init(&cb); //تهيئة المخزن 

    char name[100];
    const char suffix[] = "CE-ESY";

    printf("Enter your name: ");
    scanf("%s", name); //استقبال الاسم من المستخدم

    strcat(name, suffix); // اضافة السلسلة النصية CE-ESY 
    printf("The stored text : %s\n", name);

    for (int i = 0; i < strlen(name); i++) {
        write(&cb, name[i]);
    }

    //قراءة البيانات وعرضها حتى يفرغ المخزن
    printf("\nData from the buffer: ");
    while (!isEmpty(&cb)) {
        printf("%c", read(&cb));
    }

    // التأكد من ان المخزن فارغ
    if (isEmpty(&cb)) {
        printf("\n\n The buffer is empty.\n");
    }

    return 0;
}
