#include "calculadora.h"

int main (){
  int n1,n2, coc, res;
  char op,kk;

do{
  op=menu();
  if (op != '0') {
    pedirNumeros(&n1, &n2);
    scanf ("%c", &kk); // esta lectura elimina el return de la ultima lectura
    switch (op){
      case '+': res=sumar(n1,n2);
                printf ("Resultado =%d\n", res);
                break;
      case '-': res=restar(n1, n2);
                printf ("Resultado =%d\n", res);
                break;
      case '*': res=multiplicar(n1, n2);
                printf ("Resultado =%d\n", res);
                break;
      case '/': dividir(n1,n2, &coc,&res);
                printf ("Cocciente= %d, Resto=%d\n", coc, res);
                break;
      case '0': printf ("fin\n"); break;
      default:  printf ("Opcion erronea\n");
    }
  }
}while (op != '0');
//system ("pause");
}


