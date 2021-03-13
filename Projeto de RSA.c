#include <stdio.h>
#include <string.h>

int mdc(long long int numero1, long long int numero2)//verifica o mdc
{
	if(numero2==0)
	{
		return numero1;
	}
	else
	{
		return mdc(numero2,numero1%numero2);
	}
}

int primo(long long int numero)//verifica se o valor é primo
{
	int primo=2,i;
	if(numero==1||numero==0)
	{
		primo=1;
	}
	else
	{
		for(i=2;i<numero;i++)
		{
			if(numero%i==0)
			{
				primo=1;
				break;
			}
		}
	}
	return primo;
}

long long int fi(long long int p,long long int q)//calcula fi(n)
{
	long long int fin;
	fin=(p-1)*(q-1);
	return fin;
}

long long int chave_pub(long long int p,long long int q)//calcula a chave pública n
{
	long long int chave;
	chave=p*q;
	return chave;
}

long long int funcao(long long int base,long long int expoente,long long int modulo)//resolve exponenciação modular
{
	long long int t=1,i;
	for(i=0;i<expoente;i++)
	{
		t=t*base%modulo;
	}
	return t;
}

long long int inverso(long long int chave,long long int modulo)//calcula o inverso
{
	long long int i=1,j;
	while(i<=modulo)
	{
		j=(chave*i)%modulo;
		i++;
		if(j==1)
		{
			break;
		}	
	}
	return i-1;
}
char descripto(long long int base,long long int expoente,long long int mod)//desencripta o caractere
{
	return (char) funcao(base,expoente,mod);
}

int main()
{
	long long int escolha,primo_p,primo_q,coprimo_e,chave_n,chave_d,z,i,j,k,l;
	
	FILE *file1;//arquivo que recebe a chave pública
	FILE *file2;//arquivo que recebe mensagem criptografada
	FILE *file3;//arquivo que rece mensagem descriptografada 
	FILE *file4;//arquivo que recebe mensagem criptografada externa
	char mensagem[10000];//recebe a mensagem
	char descript[10000];//recebe a mensagem descriptografada
	long long int numero_c[10000];//recebe o valor inteiro do char depois que foi encriptado
	long long int numero[10000];//recebe o valor inteiro do char antes de ser criptado
	
	//menú
	printf("Escolha uma tarefa válida:\n");
	printf("1-Gerar chave pública\n");
	printf("2-Criptografar\n");
	printf("3-Descriptografar\n");
	printf("0-Fechar o programa \n");
	
	scanf("%lld",&escolha);//usuário escolhe a tarefa
	
	//programa fica em loop até o usuário digitar 0
	while(escolha != 0)
	{
		while(escolha<1 || escolha>3)//fica em loop até o usuário digitar uma escolha válida
		{
			printf("Escolha uma tarefa válida\n");
			scanf("%lld",&escolha);
		}
		
		if(escolha==1)//gera a chave pública
		{
			printf("escolha um primo 'p':\n");
			scanf("%lld",&primo_p);//atribui valor para o primo p
			while(primo(primo_p)==1)//fica em loop até o usuário digitar um valor primo
			{
				printf("Número inválido\n");
				scanf("%lld",&primo_p);
			}
			
			printf("escolha um primo 'q':\n");
			scanf("%lld",&primo_q);////atribui valor para o primo q
			while(primo(primo_q)==1)//fica em loop até o usuário digitar um valor primo
			{
				printf("Número invalido\n");
				scanf("%lld",&primo_q);
			}
			
			printf("escolha um expoente 'e' coprimo a %lld:\n",fi(primo_p,primo_q));
			scanf("%lld",&coprimo_e);////atribui valor para o coprimo e
			while(mdc(coprimo_e,fi(primo_p,primo_q))!=1)//fica em loop até o usuário digitar um valor válido
			{
				printf("Número inválido\n");
				scanf("%lld",&coprimo_e);
			}
			
			file1 = fopen("Chave pública.txt","a");//abre o arquivo
			fprintf(file1,"n=%lld\n",chave_pub(primo_p,primo_q));//salva a chave n no arquivo
			fprintf(file1,"e=%lld",coprimo_e);//salva a chave e no arquivo
			fclose(file1);//fecha o arquivo
			
			printf("Arquivo com a chave pública salvo no diretório de execução\n");
		}
		
		if(escolha==2)//gera o arquivo criptografado
		{
			printf("Digite a mensagem para ser encriptada:\n");
			
			getchar();
			fgets(mensagem,10000,stdin);//salva a string
			
			z=strlen(mensagem);//salva o tamanho da string
			
			for(i=0;i<z;i++)//converte o char para um valor inteiro
			{
				numero[i]=mensagem[i];
			}
			
			printf("Digite a chave pública recebida previamente,'n' e 'e' respectivamente:\n");//atribui valor para n e e
			scanf("%lld",&chave_n);
			scanf("%lld",&coprimo_e);
			
			file2=fopen("Mensagem encriptada.txt","a");//abre  o arquivo
			
			for(i=0;i<z;i++)//criptografa o valor inteiro e salva no arquivo com separador
			{
				j=numero[i];
				numero_c[i]=funcao(j,coprimo_e,chave_n);
				if(i!=z-1)
				{
					fprintf(file2,"%lld ",funcao(j,coprimo_e,chave_n));		
				}
				else
				{
					fprintf(file2,"%lld",funcao(j,coprimo_e,chave_n));	
				}	
			}
			
			fclose(file2);//fehca o arquivo
			printf("Arquivo com mensagem encriptada salva no diretório de execução\n");
		}
		
		if(escolha==3)//gera o arquivo descriptografado
		{
			printf("Digite o valor de 'p':\n");//atribui valor ao primo p
			scanf("%lld",&primo_p);
			
			printf("Digite o valor de 'q':\n");//atribui valor ao primo q
			scanf("%lld",&primo_q);
			
			printf("Digite o valor de 'e':\n");//atribui valor ao corpimo e
			scanf("%lld",&coprimo_e);
			
			chave_n=chave_pub(primo_p,primo_q);//atribui valor o n
			k=fi(primo_p,primo_q);//k recebe o valor de (p-1)*(q-1)
			chave_d=inverso(coprimo_e,k);//atribui valor ao inverso d
			
			file3 = fopen("Mensagem original.txt","a");//abre o arquivo
			file4 = fopen("Mensagem encriptada.txt","r");//abre o arquivo com a mensagem externa
			
			fscanf(file4,"%lld",&l);
			
			descript[0]=descripto(l,chave_d,chave_n);
			
			for(i=1;descript[i-1]!='\n';i++)
			{
				fscanf(file4,"%lld",&l);
				descript[i]=descripto(l,chave_d,chave_n);
			}
			
			fprintf(file3,"%s\n",descript);//grava a mensagem no arquivo 
			
			fclose(file3);//fecha o arquivo
			fclose(file4);//fecha o arquivo
			printf("Mesagem salva no diretório de execução\n");
		}
		//apresenta o menú mais uma vez
		printf("Escolha uma nova tarefa:\n");
		printf("1-Gerar chave pública\n");
		printf("2-Criptografar\n");
		printf("3-Descriptografar\n");
		printf("0-Fechar o programa \n");
		
		scanf("%lld",&escolha);
	}
	return 0;
}