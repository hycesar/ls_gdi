#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int i = 0;

void sqlIUD(SQLHDBC *dbc, char *command)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, (*dbc), &stmt);
    ret = SQLExecDirect(stmt,(SQLCHAR *)command,SQL_NTS);
}

void recoverPrint(SQLHDBC *dbc, char *command)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator[ 4 ];
    SQLCHAR CPF[11]="";
    SQLCHAR Nome[50]="";
    SQLCHAR Sexo[1]="";
    SQLCHAR Email[50]="";
    stmt=NULL;

    SQLAllocHandle(SQL_HANDLE_STMT, (*dbc), &stmt);
    ret = SQLBindCol(stmt,1,SQL_C_CHAR,CPF,sizeof(CPF),&indicator[1]);
    ret = SQLBindCol(stmt,2,SQL_C_CHAR,Nome,sizeof(Nome),&indicator[2]);
    ret = SQLBindCol(stmt,3,SQL_C_CHAR,Sexo,sizeof(Sexo),&indicator[2]);
    ret = SQLBindCol(stmt,5,SQL_C_CHAR,Email,sizeof(Email),&indicator[4]);
    ret = SQLExecDirect(stmt,(SQLCHAR *)command,SQL_NTS);
    
    while((ret=SQLFetch(stmt)) != SQL_NO_DATA)
        printf("CPF: %s \tNome: %s  \tSexo: %s \tEmail: %s", CPF, Nome, Sexo, Email);
}

void main(){
   SQLHENV env;
   SQLHDBC dbc;
   SQLHSTMT stmt;
   SQLRETURN ret;

   SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);

   SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

   SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

   SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=SQL;", SQL_NTS,NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    while(1)
    {
        printf("Action Menu \n");
        printf("1 - Insert data \n");
        printf("2 - Update Data \n");
        printf("3 - Delete data \n");
        printf("4 - Select data on table 'funcionario' \n");
        printf("5 - Exit \n");
        printf("\n Enter Number:  ");

        scanf("%d", &i);

        if(i==5)
        {
            printf("\n\n\n\tProgram exit");
            
            return 0;
        }
        else if(i==1)
        {
            char *qri;
            char *tabela;
            printf("Enter the table: ");
            fflush(stdin);
            __fpurge(stdin);
            scanf("%s",&*tabela);
            strupr(tabela);

            if(strcmp(tabela,"FUNCIONARIO") == 0)
            {
                char CPF, Nome, Sexo, DataNascimento, Email, Rua, Bairro, Numero;
                char *command;
                printf("Insert into FUNCIONARIO: CPF, Nome, Sexo, Data Nascimento, Email, Rua, Bairro, Numero: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s %s %s %s %s %s", &CPF, &Nome, &Sexo, &DataNascimento, &Email, &Rua, &Bairro, &Numero);
            }
            else if (strcmp(tabela,"TELEFONE") == 0) 
            {
                char CPF, Telefone;
                printf("Insert into TELEFONE: CPF, Telefone: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s", &CPF, &Telefone);
            }
            else if(strcmp(tabela,"CHEFE") == 0)
            {
                char CPF;
                printf("Insert into CHEFE: CPF: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s ", &CPF);
            }
            else if (strcmp(tabela,"CLIENTE") == 0) 
            {
                char CodCliente, Preco, DataCiente, CPF;
                printf("Insert into CLIENTE: CodCliente, Preco, DataCiente, CPF: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s %s", &CodCliente, &Preco, &DataCiente, &CPF);
            }
            else if (strcmp(tabela,"PROJETO") == 0) 
            {
                char CPF, NumID, CodSetor, DataInicio, Tema;
                printf("Insert into PROJETO: CPF, NumID, CodSetor, DataInicio, Tema: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s %s", &CPF, &NumID, &CodSetor, &DataInicio, &Tema);
            }
            else if (strcmp(tabela,"LEITURISTA") == 0) 
            {
                char CPF, Lider;
                printf("Insert into LEITURISTA: CPF, Lider: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s", &CPF, &Lider);
            }
            else if (strcmp(tabela,"EQUIPAMENTO") == 0) 
            {
                char CodigoEquipamento, Estado, DataCompra;
                printf("Insert into EQUIPAMENTO: CodigoEquipamento, Estado, DataCompra: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s", &CodigoEquipamento, &Estado, &DataCompra);
            }
            else if (strcmp(tabela,"SERVICO") == 0) 
            {
                char CodServico, Nome, Lider;
                printf("Insert into SERVICO: CodServico, Nome, Lider: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s", &CodServico, &Nome, &Lider);
            }
            else if (strcmp(tabela,"REALIZA") == 0) 
            {
                char CPF, CodServico, CodigoEquipamento,DataRealiza,Codigo;
                printf("Insert into REALIZA: CPF, CodServico, CodigoEquipamento, DataRealiza, Codigo: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s %s", &CodServico, &CodigoEquipamento, &DataRealiza, &Codigo);
            }
            else if (strcmp(tabela,"DEPARTAMENTO") == 0)
            {
                char CodigoRelacionamento, Nome,NumProjeto;
                printf("Insert into DEPARTAMENTO: CodigoRelacionamento, Nome,NumProjeto: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s ", &CodigoRelacionamento, &Nome, &NumProjeto );
            }
            else if (strcmp(tabela,"TRABALHA") == 0)
            {
                char CPF, CodigoRelacionamento,DataTrabalha,CodOperacao;
                printf("Insert into TRABALHA: CPF, CodigoRelacionamento, DataTrabalha, CodOperacao: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s %s ", &CPF, &CodigoRelacionamento, &DataTrabalha, &CodOperacao );
            }
            else if (strcmp(tabela,"TRABALHADOR") == 0) 
            {
                char CPF, CodigoRelacionamento,DataTrabalha,CodOperacao,Identificacao,DataSalario,ValorBruto,ValorImposto;
                printf("Insert into TRABALHADOR: CPF, CodigoRelacionamento,DataTrabalha,CodOperacao,Identificacao,DataSalario,ValorBruto,ValorImposto: \n");
                fflush(stdin);
                __fpurge(stdin);
                scanf("%s %s %s %s %s %s %s %s", &CPF, &CodigoRelacionamento, &DataTrabalha, &CodOperacao, &Identificacao, &DataSalario, &ValorBruto, &ValorImposto );
            }
            //printf("Chegou aqui");
            //system("pause");
            return 0;
        }
        else if (i==2)
        {
            //system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
        else if (i==3)
        {
            //system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
        else if(i==4)
        {
            char *con[50];
            char *comando[100];
            char *qrs[100];
            //system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("Enter the condition 'Where': ");
            fflush(stdin);
            __fpurge(stdin);
            scanf("%s", &*con);
            strcpy(comando,"SELECT * FROM FUNCIONARIO WHERE ");
            strcat(comando,con);
            *strcpy(qrs,comando);
            recoverPrint(&dbc,*qrs);
            //system("pause");
            return 0;
        }
        else 
        {
            //system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
    }
}
