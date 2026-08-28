extern volatile int i;
extern volatile char io_active;

int main(void){
    if(io_active)
        return i;
    return -1;
}