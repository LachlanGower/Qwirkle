#include "UI.h"

#define EXIT_SUCCESS    0

int main(void)
{
   UI * ui = new UI();
   ui->menu();
   std::cout << "Goodbye" << std::endl;
   delete ui;
   return EXIT_SUCCESS;
}
