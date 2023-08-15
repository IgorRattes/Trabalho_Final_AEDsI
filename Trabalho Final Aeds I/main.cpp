#include <iostream>
#include <string.h>
#define CONSTANTE 10

using namespace std;

//procedimento para modificar string
void modfic_str (char nomeum[], char nomedois[]){
	if(strlen(nomeum) == strlen(nomedois)){
		strcpy(nomeum, nomedois);
	} else if (strlen(nomeum)> strlen(nomedois)){
		strcpy(nomeum, nomedois);
		nomeum[strlen(nomedois)]='\0';
	}else {
		strncpy (nomeum, nomedois, strlen(nomedois));
	}
}
//Declarando a Classe Tipo Equipamento
class Tipo_Equipamento{
public:
  int codigo_TE;
  char descricao_TE [100];

	//Esse Construtor zera as variaveis
	Tipo_Equipamento () {
		codigo_TE=0;
		strcpy (descricao_TE, "\0");
	}
	//Procedimento para mostrar os valores das variaveis
	void mostra_tipoeqp (){
		cout << codigo_TE << "\t";
		cout << descricao_TE << "\n";
	}
};
//Declarando a Classe Departamento
class Departamento{
public:
  int codigo_D;
  char nome_D[100];
  char descricao_D [100];
  char localizacao_D[100];

	//construtor para inicializar as variaveis
	Departamento (){
		codigo_D = 0;
		strcpy (nome_D, "\0");
		strcpy (descricao_D, "\0");
		strcpy (localizacao_D, "\0");
	}
	//metodo para realizar o preenchimento das variaveis
	void AlteraDepartamento (Departamento dpto) {
		dpto.codigo_D = codigo_D;
		//modifica o codigo
		modfic_str (nome_D, dpto.nome_D);
		//modifica o nome
		modfic_str (descricao_D, dpto.descricao_D);
		//modifica a descricao
		modfic_str (localizacao_D, dpto.localizacao_D);
		//modifica a localizacao
	}
	//procedimento para mostrar
	void mostra_dept (){
		cout << codigo_D << "\t";
		cout << nome_D << "\t";
		cout << descricao_D << "\t";
		cout << localizacao_D << "\t";
	}
};
//Declarando a Classe Equipamento
class Equipamento{
public:
  int codigo_E;
	float precodeaqui_E;
	char nome_E[100];
	Tipo_Equipamento *tipo = new Tipo_Equipamento();
	Departamento *dpto = new Departamento();
	//Atribuindo valor ao objeto tipo de equipamento
	void AtribuiTipo (Tipo_Equipamento tipo){
		//Atribuindo valor do codigo
		this->tipo->codigo_TE = tipo.codigo_TE;
		//Atribuindo valor da descrição
		modfic_str (this->tipo->descricao_TE, tipo.descricao_TE);
	}
	//Procedimento para preencher o objeto departamento
	void setDpto (Departamento dpto) {
    //Atribuicao do codigo
    this->dpto->codigo_D = dpto.codigo_D;
    //Atribuicao do nome
    modfic_str (this->dpto->nome_D, dpto.nome_D);
    //Atribuicao do descricao
    modfic_str (this->dpto->descricao_D, dpto.descricao_D);
    //Atribuicao do localizacao
    modfic_str (this->dpto->localizacao_D, dpto.localizacao_D);
    }
    //Procedimento para mostrar o equipamento na tela
	  void mostrar_equipamento () {
			cout << codigo_E << "\t";
      cout << nome_E << "\t";
      printf ("%.02f\t", precodeaqui_E);
      cout << dpto->nome_D << "\t";
      cout << tipo->descricao_TE << "\n";
    }
};
//Declarando metodo menu
int menu (char titulo[]){
	int op;
	bool primeiravez = true;

	//verificando o desejo do usuario
	do {
		//titulo do menu
		cout << titulo << "\n\n";
		//menu do CRUD
		cout << "Escolha uma opção: \n\n"
			"[1] - Incluir \n"
			"[2] - Deletar \n"
			"[3] - Modificar \n"
			"[4] - Mostrar Dados\n"
			"[0] - Sair \n";
		if (!primeiravez){
			cout << "!!Opcao invalida!!" << endl;
		}else {
			//modificando a variavel para quando ja tiver rodado ao menos 1 vez
			primeiravez = false;
		}
		//Recolhendo a resposta do menu
		cout << "Opção desejada: ";
		cin >> op;
		fflush (stdin);
		system ("cls");
	}while (op < 0 || op > 4);
	return op;
}
//Procedimento para fazer o backup dos dados
void backup (Equipamento equip[], int numEquip){
	FILE *arquivo;
	char titulo[50];
	//Selecionando o arquivo para salvar os documentos
	cout<<"Insira o Nome Do arquivo: ";
	cin >> titulo;
	fflush (stdin);

	//Colocando o tipo de extenção
	strcat (titulo, ".bin");
	//Abrindo o arquivo
	arquivo = fopen (titulo, "wb");
	//verificando se o arquivo foi aberto
	try {
        if (!arquivo) {
            throw 0;
        } else {
            //Grava o tamanho do vetor
            fwrite (&numEquip, sizeof (int), 1, arquivo);

            //Gravar informacoes
            fwrite(equip, sizeof (Equipamento), numEquip + 1, arquivo);

            //Feedback da acao para o usuario
            cout << "Backup concluido";
        	}
	//caso o arquivo não tenha sido aberto
	}catch (int error) {
        if (error == 0) {
            cout << "Arquivo Não Aberto ERRO";
        }
  }
	//fechando o arquivo
	fclose (arquivo);
}
//Procedimento para mostrar dados armazenados no arquivo
void mostra_arquivo (){
	FILE *arquivo;
	Equipamento equip[CONSTANTE];

	char titulo [50];
	int limite;

	//perguntando o nome do arquivo
	cout << "Digite o nome do arquivo: ";
	cin >> titulo;
	fflush (stdin);

	//definindo a estenção do arquivo
	strcat (titulo, ".bin");

	//Abrindo o arquivo
	arquivo = fopen (titulo, "rb");

	//Validando se o arquivo foi aberto corretamente
	try {
  	if (!arquivo) {
    	throw 0;
    } else {
    		//Le o tamanho do vetor no arquivo
    		fread (&limite, sizeof(int), 1, arquivo);

    		limite++;

   			//Le o arquivo
    		fread (equip, sizeof(Equipamento), limite, arquivo);

    		//Exibe o conteudo lido dentro do arquivo
      	for (int i = 0; i < limite; i++){
    			equip[i].mostrar_equipamento();
      	}
    }
    //Caso der erro na abertura do arquivo
  } catch (int erro) {
  	if (erro == 0) {
  		cout << "Erro ao abrir o arquivo";
    }
	}
}

int main() {
	//Declarando as classes dentro do main
	Tipo_Equipamento tipos [CONSTANTE];
	Departamento deptos[CONSTANTE];
	Equipamento equip[CONSTANTE];

	//declarando variaveis comuns
	int opcao1, opcao2, i, j;
	int num, numTipo, numDepartamento, numEquip;
	char nome[50];
	bool nao_existe, primeiroLaco;

	char titulo1 [] = "Tipo de Equipamento";
	char titulo2 [] = "Departamento";

	nao_existe=true;
	primeiroLaco=true;
	numTipo=-1;
	numDepartamento=-1;
	numEquip=-1;

	//laço do para repetir o menu inicial ate que o usuario queira fechar o programa
  do {
  //Validacao da resposta
  	do {
  //Titulo da pagina
  		cout << "APRENDENDO POO" << endl << endl;
  //Primeiro menu
      cout << "Selecione qual ação deseja fazer" << endl << endl;
      cout << "Digite:" << endl
           << "[1] - Equipamento" << endl
           << "[2] - Tipo de Equipamento" << endl
           << "[3] - Departamento" << endl
           << "[0] - Sair" << endl << endl;

            //Verifica se é o primeiro laco
            if (!primeiroLaco) {
                cout << "Opcao invalida" << endl;
            } else {
                //Reajuste na variavel
                primeiroLaco = false;
            }
            //Entrada da opcao
            cout << "Sua opcao: ";
            cin >> opcao1;
            fflush (stdin);
            system ("cls");
        } while (opcao1 < 0 || opcao1 > 3);

        //Reinicia a variavel
        primeiroLaco = true;

        //switch case para os menus
        switch (opcao1) {
            //Equipamento
            case 1:
                //Validacao da resposta
                do {
                    //Exibe o titulo da pagina
                    cout << "EQUIPAMENTO" << endl << endl;

                    //Exibe o menu das opcoes
                    cout << "Digite:" << endl << endl
                         << "[1] - Incluir" << endl
                         << "[2] - Deletar" << endl
                         << "[3] - Modificar" << endl
                         << "[4] - Mostrar Dados" << endl
                         << "[5] - Backup dos dados" << endl
                         << "[6] - Listar dados do arquivo" << endl
                         << "[0] - Sair" << endl << endl;

                    //Verifica se eh o primeiro laco
                    if (!primeiroLaco) {
                        cout << "Opcao invalida" << endl;
                    } else {
                        primeiroLaco = false;
                    }

                    //Entrada da opcao
                    cout << "Sua opcao: ";
                    cin >> opcao2;
                    fflush (stdin);
                    system ("cls");
                } while (opcao2 < 0 || opcao2 > 6);

                //Reinicia a variavel
                primeiroLaco = true;

                //Switch case para as opcoes CRUD
                switch (opcao2) {
                    //Inserir equipamento
                    case 1:
                        //Exibe o titulo da pagina
                        cout << "INSERIR EQUIPAMENTO" << endl << endl;

                        try {
                            //Verifica se ha cadastro de tipo de equipamento e de departamento
                            if (numTipo == -1 || numDepartamento == -1) {
                                throw true;
                            } else {
                                //Verifica se foi alcancado o limite do vetor
                                if (numEquip < 10) {
                                    //Ajusta a posicao do vetor que as informacoes serao gravadas
                                    numEquip ++;

                                    //Entrada do codigo
                                    cout << "Insira um codigo: ";
                                    cin >> equip[numEquip].codigo_E;
                                    fflush (stdin);

                                    //Entrada do nome
                                    cout << "Insira um nome: ";
                                    scanf ("%[^\n]", equip[numEquip].nome_E);
                                    fflush (stdin);

                                    //Entrada do preco de aquisicao
                                    cout << "Insira o preco de aquisição do equipamento: ";
                                    cin >> equip[numEquip].precodeaqui_E;
                                    fflush (stdin);

                                    //Exibe os tipos de equipamentos disponiveis
                                    cout << endl << "Tipos de equipamentos disponiveis:" << endl;
                                    for (i = 0; i <= numTipo; i++) {
                                        tipos[i].mostra_tipoeqp();
                                    }

                                    //Reinicia a variavel
                                    nao_existe = true;

                                    //Validacao da resposta
                                    do {
                                        //Verifica se eh o primeiro laco
                                        if (nao_existe && !primeiroLaco) {
                                            cout << "Opcao invalida" << endl;
                                        } else {
                                            primeiroLaco = false;
                                        }

                                        //Entrada do codigo do tipo de equipamento
                                        cout << endl << "Insira o codigo do tipo de equipamento a que pertence: ";
                                        cin >> num;
                                        fflush (stdin);



                                        //Localiza o codigo do tipo de equipamento
                                        for (i = 0; i <= numTipo; i++) {
                                            if (num == tipos[i].codigo_TE) {
                                                //Agregamento das classes
                                                equip[numEquip].AtribuiTipo(tipos[i]);
                                                nao_existe = false;
                                                break;
                                            }
                                        }
                                    } while (nao_existe);

                                    //Exibe os departamentos disponiveis
                                    cout << endl << "Departamentos disponiveis: " << endl;
                                    for (i = 0; i <= numDepartamento; i++) {
                                        deptos[i].mostra_dept();
                                    }
                                    //Reinicia a variavel
                                    primeiroLaco = true;
                                    nao_existe = true;

                                    //Validacao da resposta
                                    do {
                                        //Verifica se eh o primeiro laco
                                        if (nao_existe && !primeiroLaco) {
                                            cout << "Opcao invalida" << endl;
                                        } else {
                                            primeiroLaco = false;
                                        }

                                        //Entrada do codigo do departamento
                                        cout << endl << "Insira o codigo do departamento a que pertence: ";
                                        cin >> num;
                                        fflush (stdin);

                                        //Localiza o codigo do tipo de equipamento
                                        for (i = 0; i <= numDepartamento; i++) {
                                            if (num == deptos[i].codigo_D) {
                                                //Agregamento das classes
                                                equip[numEquip].setDpto(deptos[i]);
                                                nao_existe = false;
                                                break;
                                            }
                                        }
                                    } while (nao_existe);

                                    //Reinicia a variavel
                                    primeiroLaco = true;
                                    nao_existe = true;

                                } else {
                                    //Quando alcancar o limite do vetor
                                    cout << "Limite de equipamentos cadastrados alcancado";
                                }
                            }
                        //Tratamento de erros
                        }
                        catch (bool erro) {
                            //Se houver algum cadastro faltante
                            if (erro) {
                                //Se faltar o cadastro de departamento e de tipo de equipamento
                                if (numDepartamento == -1 && numTipo == -1) {
                                    cout << "Nao ha departamento e tipo" << endl
                                         << "de equipamento cadastrado." << endl << endl
                                         << "Insira" << endl
                                         << "primeiro para habilitar essa funcionalidade.";

                                //Se faltar o cadastro de tipo de equipamento
                                } else if (numTipo == -1) {
                                    cout << "Nao ha tipo de equipamento cadastrado." << endl
                                         << "Insira primeiro para habilitar essa funcionalidade.";

                                //Se faltar o cadastro de departamento
                                } else {
                                    cout << "Nao ha departamento cadastrado." << endl
                                         << "Insira primeiro para habilitar essa funcionalidade.";;
                                }
                            }
                        }
                        break;

                    //Excluir equipamento
                    case 2:
                        //Exibe o titulo da pagina
                        cout << "EXCLUIR EQUIPAMENTO" << endl << endl;

                        //Caso nao haver nenhum cadastro de equipamento
                        if (numEquip == -1) {
                            cout << "Nao ha nenhum equipamento cadastrado." << endl
                                 << "Insira primeiro para habilitar essa funcionalidade.";

                        //Caso haver cadastros
                        } else {
                            //Exibe os equipamentos disponiveis
                            cout << "Equipamentos disponiveis:" << endl;
                            for (i = 0; i <= numEquip; i++) {
                                equip[i].mostrar_equipamento();
                            }

                            //Entrada do codigo do equipamento a ser excluido
                            cout << endl << "Insira o codigo do elemento a ser excluido: ";
                            cin >> num;
                            fflush (stdin);

                            //Acha o elemento informado
                            for (i = 0; i <= numEquip; i ++) {
                                if (num == equip[i].codigo_E) {
                                    nao_existe = false;
                                    numEquip --;

                                    //Remanejo no vetor
                                    for (j = i; j <= numEquip; j++) {
                                        //Remanejo do codigo
                                        equip[j].codigo_E = equip[j+1].codigo_E;

                                        //Remanejo do nome
                                        modfic_str (equip[j].nome_E, equip[j+1].nome_E);

                                        //Remanejo do preco
                                        equip[j].precodeaqui_E = equip[j+1].precodeaqui_E;

                                        //Remanejo do codigo do tipo de equipamento
                                        equip[j].AtribuiTipo(*equip[j+1].tipo);

                                        //Remanejo do departamento
                                        equip[j].setDpto(*equip[j+1].dpto);
                                    }

                                    //Feedback positivo do processo para o usuario
                                    cout << endl << "Equipamento excluido com sucesso";
                                }
                            }

                            //Quando o codigo nao ser encontrado
                            if (nao_existe) {
                                cout << "Equipamento nao encontrado";
                            }

                            //Reinicia a variavel
                            nao_existe = true;
                        }
                        break;

                    //Alterar equipamento
                    case 3:
                        //Titulo da pagina
                        cout << "ALTERAR EQUIPAMENTO" << endl << endl;

                        //Caso nao haver nenhum equipamento cadastrado
                        if (numEquip == -1) {
                            cout << "Nao ha nenhum equipamento cadastrado" << endl
                                 << "Insira primeiro para habilitar essa funcionalidade";
                        } else {
                            //Exibe os equipamentos disponiveis
                            cout << "Equipamentos disponiveis:" << endl;
                            for (i = 0; i <= numEquip; i++) {
                                equip[i].mostrar_equipamento();
                            }

                            //Entrada do codigo do equipamento a ser alterado
                            cout << endl << "Informe o codigo do elemento a ser alterado: ";
                            cin >> num;
                            fflush (stdin);

                            for (i = 0; i <= numEquip; i ++) {
                                //Altera o cadastro do elemento
                                if (num == equip[i].codigo_E) {
                                    //Entrada do codigo
                                    cout << "Insira um novo codigo: ";
                                    cin >> equip[i].codigo_E;
                                    fflush (stdin);

                                    //Entrada do nome
                                    cout << "Insira um novo nome: ";
                                    scanf ("%[^\n]", equip[i].nome_E);
                                    fflush (stdin);

                                    //Entrada do preco de aquisicao
                                    cout << "Insira o novo preco de aquisicao do equipamento: ";
                                    cin >> equip[i].precodeaqui_E;
                                    fflush (stdin);

                                    //Exibe os tipos de equipamentos disponiveis
                                    cout << endl << "Tipos de equipamentos disponiveis:" << endl;
                                    for (i = 0; i <= numTipo; i++) {
                                        tipos[i].mostra_tipoeqp();
                                    }

                                    //Valida a resposta
                                    do {
                                        //Entrada do codigo do tipo de equipamento
                                        cout << endl << "Insira o codigo do tipo de equipamento a que pertence: ";
                                        cin >> num;
                                        fflush (stdin);

                                        //Localiza o codigo do tipo de equipamento
                                        for (j = 0; j <= numTipo; j++) {
                                            if (num == tipos[j].codigo_TE) {
                                                //Agregamento das classes
                                                equip[numEquip].AtribuiTipo(tipos[j]);
                                                nao_existe = false;
                                                break;
                                            }
                                        }
                                    } while (nao_existe);

                                    //Reinicia a variavel
                                    nao_existe = true;

                                    do {
                                        //Exibe os departamentos disponiveis
                                        cout << endl << "Departamentos disponiveis: " << endl;
                                        for (i = 0; i <= numDepartamento; i++) {
                                            deptos[i].mostra_dept();
                                        }

                                        //Entrada do codigo do departamento
                                        cout << endl << "Insira o codigo do departamento a que pertence: ";
                                        cin >> num;
                                        fflush (stdin);

                                        //Localiza o codigo do tipo de equipamento
                                        for (j = 0; j <= numDepartamento; j++) {
                                            if (num == deptos[j].codigo_D) {
                                                //Agregamento das classes
                                                equip[i].setDpto(deptos[j]);

                                                //Reajuste na variavel
                                                nao_existe = false;
                                                break;
                                            }
                                        }
                                    } while (nao_existe);
                                }

                                //Finaliza a execucao do laço ja que ele se torna desnecessario
                                break;
                            }

                            if (nao_existe) {
                                cout << "Codigo nao encontrado";
                            }

                            //Reinicia a variavel
                            nao_existe = true;
                        }
                        break;

                    //Exibir equipamentos
                    case 4:
                        //Titulo da pagina
                        cout << "MOSTRAR EQUIPAMENTOS" << endl << endl;

                        //Caso nao haver nenhum equipamento cadastrado
                        if (numEquip == -1) {
                            cout << "Nenhum equipamento encontrado";
                        } else {
                            //Exibe os equipamentos
                            for (i = 0; i <= numEquip; i ++) {
                                equip[i].mostrar_equipamento();
                            }
                        }
                        break;

                    //Backup dos dados
                    case 5:
                        //Titulo da pagina
                        cout << "BACKUP DOS DADOS DE EQUIPAMENTOS" << endl << endl;
                        if (numEquip == -1) {
                            cout << "Nao ha nenhum equipamento cadastrado" << endl
                                 << "Insira um equipamento primeiro para habilitar essa funcionalidade";
                        } else {
                            //Faz o backup da informacoes
                            backup(equip, numEquip);
                        }
                        break;

                    //Listar dados de arquivo
                    case 6:
                        //Titulo da pagina
                        cout << "LISTAR DADOS DE ARQUIVO" << endl << endl;

                        //Lista os dados de algum arquivo
                        mostra_arquivo();
                        break;

                    //Sair
                    default:
                        opcao1 = 0;
                }
                break;

            //Tipo de equipamento
            case 2:
                //Menu tipo de equipamento
                opcao2 = menu (titulo1);

                //Switch case para as opcoes CRUD
                switch (opcao2) {
                    //Inserir tipo Equipamento
                    case 1:
                        //Titulo da pagina
                        cout << "INSERIR TIPO DE EQUIPAMENTO" << "\n\n";

                        //Verifica se o limite de departamentos cadastrados foi alcancado
                        if (numTipo < 10) {
                            //Reajusta a variavel que controla o limite atual de cadastros
                            numTipo++;

                            //Entrada do codigo
                            cout << "Insira o codigo: ";
                            cin >> tipos[numTipo].codigo_TE;
                            fflush (stdin);

                            //Entrada da descricao
                            cout << "Insira uma descricao: ";
                            scanf ("%[^\n]", tipos[numTipo].descricao_TE);
                            fflush (stdin);

                        //Caso o limite do vetor tenha alcancado
                        } else {
                            cout << "Limite de tipos de equipamentos cadastrados alcancado";
                        }
                        break;

                    //Excluir tipo de Equipamento
                    case 2:
                        //Titulo da pagina
                        cout << "EXCLUIR TIPO DE EQUIPAMENTO\n\n";

                        //Caso nao exista nenhum cadastro ainda
                        if (numTipo == -1) {
                            cout << "Nao ha nenhum tipo de equipamento cadastrado" << "\n"
                                    "Insira um tipo de equipamento primeiro para habilitar essa funcionalidade";

                        //Exclui um cadastro de tipo de equipamento
                        } else {
                            //Exibe os tipos de equipamentos disponiveis
                            cout << endl << "Tipos de equipamentos disponiveis: " << endl;
                            for (i = 0; i <=numTipo; i++) {
                                tipos[i].mostra_tipoeqp();
                            }

                            //Entrada do codigo
                            cout << endl << "Insira o codigo do elemento a ser excluido: ";
                            cin >> num;
                            fflush (stdin);

                            //Acha o elemento informado
                            for (i = 0; i <= numTipo; i ++) {
                                if (num == tipos[i].codigo_TE) {
                                    //Remanejo no vetor
                                    for (j = i; j < numTipo; j++) {
                                        tipos[j].codigo_TE = tipos[j+1].codigo_TE;

                                        //Remanejo da descricao
                                        modfic_str (tipos[j].descricao_TE, tipos[j+1].descricao_TE);
                                    }

                                    //Feedback para o usuario do sucesso da execucao do processo
                                    cout << "\n" << "Elemento excluido com sucesso.";

                                    //Reajuste nas variaveis
                                    numTipo--;
                                    nao_existe = false;

                                    //Finaliza a execucao do laço ja que ele se torna desnecessario
                                    break;
                                }
                            }

                            //Quando o cadastro nao ser encontrado
                            if (nao_existe) {
                                cout << "Codigo nao encontrado";
                            }
                        }

                        //Reinicia a variavel
                        nao_existe = true;
                        break;
                    case 3:
                        //Caso nao haver nenhum cadastro
                        if (numTipo == -1) {
                            //Titulo da pagina
                            cout << "ALTERAR TIPO DE EQUIPAMENTO" << "\n\n";

                            //Mensagem de erro
                            cout << "Nao ha nenhum tipo de equipamento cadastrado." << "\n"
                                    "Insira primeiro para habilitar essa funcionalidade.";
                        } else {
                            //Valida a resposta
                            do {
                                //Titulo da pagina
                                cout << "ALTERAR TIPO DE EQUIPAMENTO" << "\n\n";

                                //Informa como deseja achar o elemento
                                cout << "Como deseja indentificar o tipo de equipamento?" << endl << endl;
                                cout << "Digite:" << endl
                                    << "[1] - codigo" << endl
                                    << "[2] - descricao" << endl;
                                cout << "Sua opcao: ";
                                cin >> num;
                                fflush (stdin);
                                system ("cls");
                            } while (num < 1 || num > 2);

                            //Titulo da pagina
                            cout << "ALTERAR TIPO DE EQUIPAMENTO" << "\n\n";

                            //Exibe os tipos de equipamentos disponiveis
                            cout << "Tipos de equipamentos disponiveis: " << endl;
                            for (i = 0; i <=numTipo; i++) {
                                tipos[i].mostra_tipoeqp();
                            }

                            //Altera o cadastro de um elemento
                            if (num == 1) {
                                //Entrada do codigo
                                cout << endl << "Insira o codigo do elemento a ser alterado: ";
                                cin >> num;
                                fflush (stdin);

                                //Acha o elemento digitado
                                for (i = 0; i <= numTipo; i ++) {
                                    //Altera o cadastro do elemento
                                    if (num == tipos[i].codigo_TE) {
                                        //Alteracao do codigo
                                        cout << "Insira um novo codigo: ";
                                        cin >> tipos[i].codigo_TE;
                                        fflush (stdin);

                                        //Alteracao da descricao
                                        cout << "Insira uma nova descricao: ";
                                        scanf ("%[^\n]", tipos[i].descricao_TE);
                                        fflush (stdin);

                                        //Certifica que o cadastro foi encontrado
                                        nao_existe = false;
                                        break;
                                    }
                                }
                            } else {
                                //Entrada da descricao
                                cout << "Insira a descricao do elemento a ser alterado: ";
                                scanf ("%[^\n]", nome);
                                fflush (stdin);

                                //Acha o elemento digitado
                                for (i = 0; i <= numTipo; i ++) {
                                    //Altera o cadastro do elemento
                                    if (strcmp(nome, tipos[i].descricao_TE) == 0) {
                                        //Alteracao do codigo
                                        cout << "Insira um novo codigo: ";
                                        cin >> tipos[i].codigo_TE;
                                        fflush (stdin);

                                        //Alteracao da descricao
                                        cout << "Insira uma nova descricao: ";
                                        scanf ("%[^\n]", tipos[i].descricao_TE);
                                        fflush (stdin);

                                        //Certifica que o cadastro foi encontrado
                                        nao_existe = false;
                                        break;
                                    }
                                }
                            }

                            //Quando o cadastro nao ser encontrado
                            if (nao_existe) {
                                cout << "Codigo nao encontrado";
                            }

                            //Reinicia a variavel
                            nao_existe = true;
                        }
                        break;
                    case 4:
                        //Titulo da pagina
                        cout << "LISTA TIPO DE EQUIPAMENTO" << "\n\n";

                        //Caso nao tenha nenhum departamento cadastrado
                        if (numTipo == -1) {
                            cout << "Nenhum tipo de equipamento encontrado";

                        //Lista os departamentos cadastrados
                        } else {
                            for (i = 0; i <= numTipo; i++) {
                                tipos[i].mostra_tipoeqp();
                            }
                        }
                        break;
                    default:
                        opcao1 = 0;
                }
                break;

            //Departamento
            case 3:
                //Menu Departamento
                opcao2 = menu (titulo2);

                //Switch case para as opcoes CRUD
                switch (opcao2) {
                    //Inserir novo departemento
                    case 1:
                        //Titulo da pagina
                        cout << "INSERIR DEPARTAMENTO" << "\n\n";

                        //Verifica se o limite de departamentos cadastrados foi alcancado
                        if (numDepartamento <= 9) {
                            //Reajusta a variavel que controla o limite atual de cadastros
                            numDepartamento++;

                            //Entrada do codigo
                            cout << "Insira o codigo: ";
                            cin >> deptos[numDepartamento].codigo_D;
                            fflush (stdin);

                            //Entrada do nome
                            cout << "Insira o nome: ";
                            cin >> deptos[numDepartamento].nome_D;
                            fflush (stdin);

                            //Entrada da descricao
                            cout << "Insira uma descricao: ";
                            scanf ("%[^\n]", deptos[numDepartamento].descricao_D) ;
                            fflush (stdin);

                            //Entrada da localizacao
                            cout << "Insira uma localizacao: ";
                            scanf ("%[^\n]", deptos[numDepartamento].localizacao_D);
                            fflush (stdin);

                        //Caso o limite do vetor tenha alcancado
                        } else {
                            cout << "Limite máximo atingido";
                        }
                        break;

                    //Excluir um departamento
                    case 2:
                        //Titulo da pagina
                        cout << "EXCLUIR DEPARTAMENTO" << "\n\n";

                        //Caso nao tenha nenhum cadastro de departamento
                        if (numDepartamento == -1) {
                            cout << "Nao ha nenhum departamento cadastrado" << "\n"
                                    "Insira primeiro para habilitar essa funcionalidade";

                        //Exclui um departamento
                        } else {
                            //Exibe os departamentos disponiveis
                            cout << endl << "Departamentos disponiveis: " << endl;
                            for (i = 0; i <= numDepartamento; i++) {
                                deptos[i].mostra_dept();
                            }

                            //Entrada do codigo
                            cout << endl << "Insira o codigo do elemento a ser excluido: ";
                            cin >> num;
                            fflush (stdin);

                            //Achar o elemento informado
                            for (i = 0; i <= numDepartamento; i ++) {
                                if (num == deptos[i].codigo_D) {
                                    //Remanejo no vetor
                                    for (j = i; j < numDepartamento; j++) {
                                        deptos[j].AlteraDepartamento(deptos[j+1]);
                                    }
                                    //Feedback para o usuario do sucesso da execucao do processo
                                    cout << "\n" << "Elemento excluido com sucesso.";

                                    //Reajuste nas variaveis
                                    numDepartamento--;
                                    nao_existe = false;
                                }
                            }

                            //Quando o cadastro nao ser encontrado
                            if (nao_existe) {
                                cout << "Codigo nao encontrado";
                            }

                            //Reinicia a variavel
                            nao_existe = true;
                        }
                        break;

                    //Alterar um departamento
                    case 3:
                        //Titulo da pagina
                        cout << "ALTERAR DEPARTAMENTO" << "\n\n";

                        //Caso nao tenha nenhum departamento cadastrado
                        if (numDepartamento == -1) {
                            cout << "Nao ha nenhum departamento cadastrado" << "\n"
                                    "Insira primeiro para habilitar essa funcionalidade";

                        //Altera o cadastro de um departamento
                        } else {
                            //Exibe os departamentos disponiveis
                            cout << "Departamentos disponiveis:" << endl;
                            for (i = 0; i <= numDepartamento; i++) {
                                deptos[i].mostra_dept();
                            }

                            //Entrada do codigo
                            cout << endl << "Insira o codigo do departamento: ";
                            cin >> num;
                            fflush (stdin);

                            //Acha o elemento digitado
                            for (i = 0; i <= numDepartamento; i ++) {
                                //Modifica o cadastro do elemento
                                if (num == deptos[i].codigo_D) {
                                    //Altera o codigo do departamento
                                    cout << "Insira um novo codigo: ";
                                    cin >> deptos[i].codigo_D;
                                    fflush (stdin);

                                    //Altera o nome do departamento
                                    cout << "Insira uma novo nome: ";
                                    scanf ("%[^\n]", deptos[i].nome_D);
                                    fflush (stdin);

                                    //Altera a descricao do departamento
                                    cout << "Insira uma nova descricao: ";
                                    scanf ("%[^\n]", deptos[i].descricao_D);
                                    fflush (stdin);

                                    //Altera a localizacao do departamento
                                    cout << "Insira uma nova localizacao: ";
                                    scanf ("%[^\n]", deptos[i].localizacao_D);
                                    fflush (stdin);

                                    //Certifica que o cadastro foi encontrado e alterado
                                    nao_existe = false;
                                }
                            }

                            //Quando o cadastro nao ser encontrado
                            if (nao_existe) {
                                cout << "Codigo nao encontrado";
                            }

                            //Reinicia a variavel
                            nao_existe = true;
                        }
                        break;

                    //Mostrar departamentos
                    case 4:
                        //Titulo da pagina
                        cout << "LISTAR DEPARTAMENTO" << "\n\n";

                        //Caso nao haver nenhum cadastro
                        if (numDepartamento == -1) {
                            cout << "Nenhum departamento encontrado";

                        //Lista todos os cadastros de Departamentos
                        } else {
                            for (i = 0; i <= numDepartamento; i++) {
                                deptos[i].mostra_dept();
                            }

                            //Repete o filtro
                            do {
                                //Informa se o usuario deseja fazer um filtro
                                cout << "\n\n" << "Digite:" << "\n"
                                        "[1] - Inserir filtro por nome" << "\n"
                                        "[0] - Continuar" << "\n"
                                        "Sua opcao: ";
                                cin >> num;
                                fflush (stdin);

                                //Caso o usuario desejar inserir um filtro
                                if (num == 1) {
                                    //Informa o nome a ser filtrado
                                    cout << "\n" << "Informe um nome: ";
                                    cin >> nome;
                                    fflush (stdin);
                                    system ("cls");

                                    //Titulo da pagina
                                    cout << "FILTRAR POR NOME" << "\n\n";

                                    //Reinicia a variavel
                                    nao_existe = true;

                                    //Acha os elementos com o mesmo nome do filtro
                                    for (i = 0; i <= numDepartamento; i++) {
                                        if (strcmp (nome, deptos[i].nome_D) == 0) {
                                            deptos[i].mostra_dept();

                                            nao_existe = false;
                                        }
                                    }

                                    //Caso o nome do filtro inserido nao existir
                                    if (nao_existe) {
                                        cout << "Nenhum departamento com o nome '" << nome << "' encontrado.";
                                    }

                                //Seja uma opcao invalida
                                } else if (num != 0) {
                                    system ("cls");

                                    //Titulo da pagina
                                    cout << "LISTAR DEPARTAMENTO" << "\n\n";
                                    cout << "opcao invalida";
                                }
                            } while (num >= 1 || num < 0);
                        }
                        break;

                    //Sair
                    default:
                        opcao1 = 0;
                }
                break;
        }

        //Preparo para reiniciar o programa
        if (opcao1 != 0 ) {
            cout << "\n\n" << "Pressione 'enter' para continuar";
            getchar ();
            system ("cls");
        }
	}while (opcao1 !=0);
	return 0;
}
