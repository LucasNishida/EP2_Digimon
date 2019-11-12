#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->idade = -1;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->ant;
	}
	printf("\n\n");
}


int consultarIdade(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, int idade){
	    if (idade < 0 || id < 0) return false;
    	PONT id_a = buscarID(f, id);
    	if(id_a) return false;
    	
    	PONT p = (PONT) malloc (sizeof(ELEMENTO));
    	p -> id = id;
    	p -> idade = idade;

    	if(idade >= IDADEPREFERENCIAL){
    	    if(f->cabeca->prox == f->cabeca){
    	        f->cabeca->ant = p;
    	        f->cabeca->prox = p;
    	        p->prox = f->cabeca;
    	        p->ant = f->cabeca;
		return true;
            }
            if(f->cabeca->prox != f->cabeca && f->inicioNaoPref == f->cabeca){
	    	p->prox = f->cabeca;
	    	p->ant = f->cabeca->ant;
	    	f->cabeca->ant->prox = p;
	    	f-> cabeca->ant = p;
	    	return true;
	    }
	    if(f->cabeca->prox != f->cabeca && f->inicioNaoPref != f->cabeca){
	    	p->prox = f->inicioNaoPref;
	    	p->ant = f->inicioNaoPref->ant;
	    	f->inicioNaoPref->ant->prox = p;
	    	f->inicioNaoPref->ant = p;
	    	return true;
	    }
    	}
    	if(idade < IDADEPREFERENCIAL){
	    p->ant = f->cabeca->ant;
	    p->prox = f->cabeca;
	    f->cabeca->ant->prox = p;
	    f->cabeca->ant = p;
	    return true;
     	}

	return false;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){
	if(f->cabeca->prox == f->cabeca) return false;
	
	PONT apagar = f->cabeca->prox;
	*id = apagar->id;

	if(f->cabeca->prox != f->inicioNaoPref){
	    f->cabeca->prox = f->cabeca->prox->prox;
	    f->cabeca->prox->ant = f->cabeca;
	    free(apagar);
	    return true;
	}
	
	else if(f->cabeca->prox == f->inicioNaoPref){
  	    f->cabeca->prox = f->cabeca->prox->prox;
	    f->cabeca->prox->ant = f->cabeca;
	    f->inicioNaoPref = f->cabeca->prox;
	    free(apagar);
	    return true;
	}

	return false;
}


bool desistirDaFila(PFILA f, int id){
    	if(f->cabeca->prox == f->cabeca) return false;

	PONT desiste = buscarID(f, id);
	if(!desiste) return false;

	return false;
}
