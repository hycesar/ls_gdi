cv--Item 1 Este item ja foi feito no script de criacao de tipos.

--Item 2 Este item ja foi feito no script de criacao de tipos.

--Item 3 e 4 (criamos um tipo trabalhador que possui nome, tipo instrumento e tipo cursos feitos)

CREATE or REPLACE type tp_cursos as object(
	nome varchar2(50)
);
/
CREATE or REPLACE TYPE tp_cursos_feitos as VARRAY(10) OF tp_cursos;
/
CREATE or REPLACE type tp_instrumentos as object(
	nome varchar2(50);
);
/
CREATE type tp_instrumentos_usados as table of tp_instrumentos;
/
CREATE or REPLACE type tp_trabalhador as object(
	nome varchar2(50),
	instumento_trabalho tp_cursos_feitos,
	cursos_feitos tp_cursos_feitos
)NOT FINAL;
/
-- item 5
--Cria um tipo ferramenta e um construtor que recebe 3 parametros e define o ano de validade 
--como a soma entre o ano de fabricação e o tempo de validade.

CREATE OR REPLACE TYPE tp_ferramenta AS OBJECT
(
	nome VARCHAR2(50),
	ano_fab INTEGER,
	tempo_val INTEGER,
	ano_val INTEGER,

	CONSTRUCTOR FUNCTION tp_ferramenta(nome VARCHAR2, ano_fab INTEGER , tempo_val INTEGER)
    	RETURN SELF AS RESULT
);
/
CREATE OR REPLACE TYPE BODY tp_ferramenta AS
  CONSTRUCTOR FUNCTION tp_ferramenta(nome VARCHAR2, ano_fab INTEGER , tempo_val INTEGER)
  RETURN SELF AS RESULT
  AS
  BEGIN
    SELF.nome := nome;
    SELF.ano_fab := ano_fab;
    SELF.tempo_val := tempo_val;
    SELF.ano_val := tempo_val + ano_fab;
    RETURN;    
  END;
END;
/

-- item 6 Criação e chamada de um função membro em um comando SELECT e em um bloco PL

ALTER TYPE tp_funcionario 
	ADD MEMBER FUNCTION salarioAnual RETURN NUMBER CASCADE;
ALTER TYPE tp_funcionario 
	ADD ATTRIBUTE ( salario NUMBER(20)) CASCADE; 
	
CREATE OR REPLACE TYPE BODY tp_funcionario AS

	MEMBER FUNCTION salarioAnual RETURN NUMBER IS
		BEGIN
			RETURN salario * 12 ;
		END;
	END;
/
SELECT T.nome FROM tb_funcionario_tecnico T
WHERE T.salarioAnual() > 200000;

--BLOCO PL

DECLARE
func tp_funcionario_leiturista;
salarioAnual NUMBER;
BEGIN
	SELECT VALUE(f) INTO func FROM tp_leiturista f
	WHERE f.cpf=44612023454;

	salarioAnual := func.salarioAnual();
	DBMS_OUTPUT.PUT_LINE('Salario do tecnico: '||salarioAnual);
END;
/



/*********************************************CHECKLIST OR**************************************************************/

-- ITEM 7 - 
 
-- ITEM 10 - REDEFINICAO DE METODO DO SUPERTIPO DENTRO SUBTIPO (OVERRIDING)
-- FALTA PL 
-- ITEM 9 DEFINICAO DE METODO ABSTRATO E OVERRIDING NA CLASSE TECNICO ?????????????????????
	-- SE SIM, FALTA FZR A CHAMADA PRA ESSE METODO


ALTER TYPE tp_funcionario
	ADD MAP MEMBER FUNCTION funcToInt RETURN NUMBER CASCADE;
	--adicionado na superclasse para leiturista poder adicionar metodo MAP tambem

ALTER TYPE tp_leiturista 
	ADD OVERRIDING MAP MEMBER FUNCTION funcToInt RETURN NUMBER CASCADE;
	--define funcao para leiturista ordenada pelo numeroCadastro do tecnico
CREATE OR REPLACE TYPE BODY tp_funcionario_tecnico AS
	OVERRIDING MAP MEMBER FUNCTION funcToInt RETURN NUMBER IS
		BEGIN
			RETURN numeroCadastro;
		END;
	END;
/

--consulta para obter os leiturista que fizeram leitura no endereço

