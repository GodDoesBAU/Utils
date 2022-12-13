#include "EzArray.h"

//_____________________________________________________________

	List crea_lista(int dim_elemento){
		List lista;
		
		lista.n_elementi=0;
		lista.u_dim = dim_elemento;
		lista.actual_dim=sizeof(lista);
		lista.pointer = NULL;
			
		return lista;	
	}
	
	List l_fromArray(void * array, int dim_elemento, int n_elementi){
		List lista;
		
		if(dim_elemento > 0){
			lista.n_elementi=n_elementi;
			lista.u_dim = dim_elemento;
			lista.pointer = malloc(dim_elemento*n_elementi);
			
			if(lista.pointer){
				if(memcpy(lista.pointer, array, dim_elemento*n_elementi)){
					aggiorna_dim(&lista);
					
					return lista;
				
				}
			}
		}
		
		return crea_lista(dim_elemento);
	}
	
	List l_fromElement(int dim_elemento, void *elemento){
		List l;
		l=crea_lista(dim_elemento);
		l_append(&l, elemento);
		
		return l;
	}
	
	//_____________________________________________________________
	
	int l_append(List * l, void *elemento){
		
		void *temp;
		temp = malloc((l->n_elementi+1) * l->u_dim);
		
		if(temp){
			if(memcpy(temp, l->pointer, l->n_elementi * l->u_dim)){
				if(memcpy(temp + (l->n_elementi * l->u_dim) , elemento, l->u_dim)){
					free(l->pointer);
					l->pointer=temp;
					l->n_elementi++;
					aggiorna_dim(l);
					return 1;
					
				}else
					return -3;
					
			}else
				return -3;
		
		}else
			return -1;
		
		return 0;
	}
	
	void * l_pop(List *l){
		void *element;
		element=NULL;
		
		if(l->n_elementi>0){
			
			void *temp;
			temp = malloc((l->n_elementi-1)* l->u_dim);
			if(temp){
				
				element = malloc(l->u_dim);
				if(element){
			
					if(memcpy(element, l->pointer , l->u_dim)){
						
						if(memcpy(temp, l->pointer + l->u_dim , (l->n_elementi-1) * l->u_dim)){
								free(l->pointer);
								l->pointer=temp;
								l->n_elementi--;
								aggiorna_dim(l);
								
						}
					}
				}
			}
		}
		
		return element;
	}
	
	List l_clone(List *l){
		List clone;
		clone.n_elementi = l->n_elementi;
		clone.u_dim = l->u_dim;
		clone.pointer = malloc(l->n_elementi * l->u_dim);
		
		if(clone.pointer){
			int c=0, ok=1;
			while(c < l->n_elementi){
				
				if(ok){
					if(!memcpy(clone.pointer + (c * l->u_dim), l->pointer + (c * l->u_dim), l->u_dim) )
						ok=0;
					
					c++;
				}
			}
			
			if(ok){
				aggiorna_dim(&clone);
				return clone;	
			}
		}
		
		return crea_lista(l->u_dim);
	}
	
	List l_matches(List *l, List *l2){
		
		if(l->u_dim == l2->u_dim){
			int offset = l->u_dim;
			List matches = crea_lista(offset);
			int i_l2,  i_l, status;
			i_l=0;
			
			while(i_l < l->n_elementi){
				i_l2 = 0;
				
				while(i_l2 < l2->n_elementi){
					if(memcmp(l->pointer + (i_l * offset), l2->pointer + (i_l2 * offset), offset)==0){
						l_append(&matches, l->pointer + (i_l * offset));
						break;
					}
					i_l2++;
				
				}
				i_l++;
			
			}
			
			return matches;
			
		}else
			return crea_lista(sizeof(int));
			
	}
	
	int l_insert(List *destinazione, List *da_inserire, int startindex){
		
		if(startindex > -1 && startindex <= destinazione->n_elementi){
			
			if(destinazione->u_dim == da_inserire->u_dim){
				
				int dim= destinazione->u_dim;
				void *completa= malloc((destinazione->n_elementi + da_inserire->n_elementi) * destinazione->u_dim);
				if(completa){
					int ok=0;
					memcpy(completa , destinazione->pointer, dim * startindex) ? ok++ : ok--;
					memcpy(completa + (dim * startindex), da_inserire->pointer, da_inserire->n_elementi * dim)!=NULL ? ok++ : ok--;
					memcpy(completa + (da_inserire->n_elementi + startindex) * dim, destinazione->pointer + (startindex * dim), (destinazione->n_elementi - startindex) * dim)!=NULL ? ok++ : ok--;
					
					if(ok == 3){
						free(destinazione->pointer);
						destinazione->pointer = completa;
						destinazione->n_elementi+=da_inserire->n_elementi;
						aggiorna_dim(destinazione);
						return 1;
					
					}else
						return -3;
						
				}else
					return -1;
				
			}else
				return -4;
		
		}else 
			return -2;
			
	}
	
	int l_remove(int index, List *l){
		void *temp;
		temp = malloc((l->n_elementi-1)* l->u_dim);
		
		if(temp){
			
			if(index > -1 && index < l->n_elementi){
				int elemento = l->u_dim;
				
				int ok=0;
				memcpy(temp, l->pointer, elemento * index) ? ok++ : ok-- ;
				memcpy(temp + elemento * index, l->pointer + ((index + 1) * elemento), elemento * (l->n_elementi - index)) ? ok++ : ok-- ;
				
				if(ok==2){
					free(l->pointer);
					l->pointer = temp;
					l->n_elementi--;
					aggiorna_dim(l);
					return 1;
					
				}else
					return -3;
					
			}else
				return -2;
			
		}else
			return -1;
			
	}
	
	int l_removeElements(List *l, List *da_sottrarre){
		
		if(l->u_dim == da_sottrarre->u_dim){
			int offset = l->u_dim;
			int i_da_sottrarre,  i_l, status;
			i_l=0;
			
			while(i_l < l->n_elementi){
				i_da_sottrarre = 0;
				
				while(i_da_sottrarre < da_sottrarre->n_elementi){
					if(memcmp(l->pointer + (i_l * offset), da_sottrarre->pointer + (i_da_sottrarre * offset), offset)==0){
						status = l_remove(i_l, l);
						
						if(status){
							i_l--;
							break;
						
						}else
							return status;
					}
					i_da_sottrarre++;
				}
				i_l++;
			}
			
			return 1;
			
		}else
			return -4;
			
	}
	
	int l_replace(int index, void *element, List *l){
		if(element){
			if(index > -1 && index < l->n_elementi){
				if( memcpy( l->pointer + (l->u_dim * index) , element, l->u_dim) )
					return 1;
				
				return -3;
				
			}
			return -2;
			
		}
		return -5;
	}
	
	int l_find(void *element, int element_size, List *l, int element_offset){
		if(element_size + element_offset < l->u_dim){
			int 
			trovato,
			i=0;
			while(i < l->n_elementi){
				trovato = memcmp(l->pointer + (l->u_dim * i) + element_offset, element, element_size);
				if(trovato == 0)
					return i;
				
				i++;
			}
				
		}
		
		return -6;
			
	}
	
	List l_findall(void *element, int element_size, List *l, int element_offset){
		List match= crea_lista(sizeof(int));
		
		if(element_size + element_offset < l->u_dim){
			int 
			trovato,
			i=0;
			while(i < l->n_elementi){
				trovato= memcmp(l->pointer + (l->u_dim * i) + element_offset, element, element_size);
				if(trovato == 0)
					l_append(&match, &i);
					
				i++;
			}
				
		}
		
		return match;
	}
	
	void * l_index(int index, List *l){
		void *element= malloc(l->u_dim);
		if(element){
			if(index > -1 && index < l->n_elementi){
				if( memcpy( element, l->pointer + (l->u_dim * index), l->u_dim) )
					return element;
			
			}
						
		}
				
		return NULL;
	}
	
	int l_change_type(List *l, int newsize){
		if(l->n_elementi != 0)
			destroy(l);
		
		l->u_dim = newsize;
		
		return 1;
	}
	
	int is_in(List *l, void *elemento){
		int i_l=0;
		int trovato;
		
		while(i_l < l->n_elementi){
			trovato=memcmp(l->pointer + (l->u_dim * i_l), elemento, l->u_dim);
			if(trovato==0)
				return 1;
			i_l++;
		}
		
		return 0;
	}
	
	char * l_tostring(List *l){
		if(l->u_dim == sizeof(char)){
			char *string;
			string = (char *) malloc(l->n_elementi);
			
			if(memcpy(string, l->pointer, l->n_elementi)){
				return string;
			}
		}
		
		return NULL;	
	}
	
	void destroy(List *l){
		free(l->pointer);
		l->pointer= NULL;
		l->n_elementi=0;
		aggiorna_dim(l);
	}
	
	//_____________________________________________________________
	
	void aggiorna_dim(List * l){
		l->actual_dim = sizeof(List) + l->u_dim * l->n_elementi;
	}
	
//_________________________________________________________________
