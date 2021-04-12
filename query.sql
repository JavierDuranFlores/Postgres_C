CREATE DATABASE hospitalu;

CREATE TABLE pacientes (
    ID SMALLSERIAL,
    nombre CHARACTER VARYING(20) NOT NULL,
    apellidoP CHARACTER VARYING(20) NOT NULL,
    apellidoM CHARACTER VARYING(20) NOT NULL,
    sexo CHARACTER VARYING(1) NOT NULL,
    edad INT,
    telefono CHARACTER VARYING(20) NOT NULL,
    calle CHARACTER VARYING(20) NOT NULL,
    numero INT,
    ciudad CHARACTER VARYING(20) NOT NULL,
    
    CONSTRAINT pk_pacientes_id PRIMARY KEY(ID),
    CONSTRAINT ck_pacientes_sexo CHECK (sexo ~ '^[HM]$'),
    CONSTRAINT ck_pacientes_edad CHECK (edad > 0 AND edad < 100),
    CONSTRAINT ck_pacientes_telefono CHECK (telefono ~ '[\(]?[\+]?(\d{2}|\d{3})[\)]?[\s]?((\d{6}|\d{8})|(\d{3}[\*\.\-\s]){3}|(\d{2}[\*\.\-\s]){4}|(\d{4}[\*\.\-\s]){2})|\d{8}|\d{10}|\d{12}')
);

INSERT INTO pacientes (nombre, apellidop, apellidom, sexo, edad, telefono, calle, numero, ciudad) 
VALUES ('Mateo', 'Benitez', 'Juan', 'H', 35, '8329352305', 'Agustin Lara', 69, 'Tuxtepec'),
       ('Josefina', 'Enriquez', 'Peña', 'M', 29, '6598896726', 'Av. Independencia', 241, 'Tuxtepec'),
       ('Agustina', 'Carrera', 'Negrete', 'M', 26, '6967504549', 'av. Independencia', 749, 'Tuxtepec'),
       ('Victoria Eugenia', 'Cuevas', 'Jimenez', 'M', 31, '7809804335', 'Av. 20 de noviembre', 1024, 'Tuxtepec'),
       ('Camilo', 'Mora', 'Muñoz', 'H', 33, '6923131823', 'Carretera loma alta', 45, 'Tuxtepec');

CREATE TABLE medicos (
    ID SMALLSERIAL,
    nombre CHARACTER VARYING(20) NOT NULL,
    apellidoP CHARACTER VARYING(20) NOT NULL,
    apellidoM CHARACTER VARYING(20) NOT NULL,
    sexo CHARACTER VARYING(1) NOT NULL,
    edad INT,
    telefono CHARACTER VARYING(20) NOT NULL,
    CONSTRAINT pk_medicos_id PRIMARY KEY(ID),
    CONSTRAINT ck_medicos_sexo CHECK (sexo ~ '^[HM]$'),
    CONSTRAINT ck_medicos_edad CHECK (edad > 0 AND edad < 100),
    CONSTRAINT ck_pacientes_telefono CHECK (telefono ~ '[\(]?[\+]?(\d{2}|\d{3})[\)]?[\s]?((\d{6}|\d{8})|(\d{3}[\*\.\-\s]){3}|(\d{2}[\*\.\-\s]){4}|(\d{4}[\*\.\-\s]){2})|\d{8}|\d{10}|\d{12}')
);

INSERT INTO medicos (nombre, apellidoP, apellidoM, sexo, edad, telefono)
VALUES ('Rosalia', 'Trujillo', 'Hernandez', 'M', 38, '8942603494'),
       ('Martha Patricia', 'Xuconostli', 'Palma', 'M', 35, '7984329988'),
       ('Alberto', 'Limon', 'Mendoza', 'H', 39, '6656710078'),
       ('Jose luis', 'Perez', 'Gonzalez', 'H', 40, '8780222030'),
       ('Oscar', 'Arreola', 'Peregrina', 'H', 48, '7476706847');

CREATE TABLE consultas (
    ID SMALLSERIAL,
    IDP INT,
    IDM INT,
    fecha DATE DEFAULT NOW(),especialidad_medicos
    CONSTRAINT pk_consultas_id PRIMARY KEY(ID),
    CONSTRAINT fk_consultas_pacientes_idp FOREIGN KEY (IDP) 
        REFERENCES pacientes (ID) ON UPDATE RESTRICT ON DELETE RESTRICT,
   CONSTRAINT fk_consultas_medicos_idm FOREIGN KEY (IDM)
        REFERENCES medicos (ID) ON UPDATE RESTRICT ON DELETE RESTRICT
);

INSERT INTO consultas (idp, idm) VALUES (1, 1), (2, 2), (3, 3), (4, 4), (5, 5);

CREATE TABLE especialidad (
    id SMALLSERIAL,
    especialidad CHARACTER VARYING(20) UNIQUE,
    
    CONSTRAINT pk_especialidad_id PRIMARY KEY (id)
);

ALTER TABLE especialidad RENAME CONSTRAINT pk_especialidad_medicos_id TO pk_especialidad_id;


INSERT INTO especialidad (especialidad) VALUES ('Cardiología'), ('Pediatría'), ('Neumología'), ('Nutriología'), ('Psiquiatría');

CREATE TABLE medicamentos (
    ID SMALLSERIAL,
    nombre CHARACTER VARYING(30) UNIQUE,
    IDE INT,
    CONSTRAINT pk_medicamentos_id PRIMARY KEY(ID),
    CONSTRAINT fk_medicamentos_especialidad_medicos_id FOREIGN KEY (IDE)
        REFERENCES especialidad (ID) ON UPDATE RESTRICT ON DELETE RESTRICT
);
-- FARMACOS Cardiovasculares
INSERT INTO medicamentos (nombre, ide) VALUES ('Fármacos Inotrópicos', 1), ('Fármacos Lusitrópicos', 1), ('Fármacos cronotrópicos', 1), ('Fármacos presores', 1);

-- FARMACOS pediatría
INSERT INTO medicamentos (nombre, ide) VALUES ('Captopril', 2), ('Minoxidil', 2), ('Hidralacina', 2), ('Espironolactona', 2), ('Propanolol', 2), ('Furosemida', 2);

-- FARMACOS Neumología
INSERT INTO medicamentos (nombre, ide) VALUES ('Alfa-dornasa', 3), ('Ambroxol', 3), ('Aminofilina', 3), ('Benzonatato', 3), ('Beractant', 3), ('Budesonida', 3);

-- FARMACOS Nutriología
INSERT INTO medicamentos (nombre, ide) VALUES ('Tiamina (B1)', 4), ('Riboflavina (B2)', 4), ('Niacina (B3)', 4), ('Piridoxina (B6)', 4), ('Cianocobalamina (B12)', 4);

-- FARMACOS Psiquiatría
INSERT INTO medicamentos (nombre, ide) VALUES ('Clorpromazina', 5), ('Flufenazina', 5), ('Haloperidol', 5);

INSERT INTO especialidad_medicos (especialidad) VALUES ('Cardiología'), ('Pediatría'), ('Neumología'), ('Nutriología'), ('Psiquiatría');

CREATE TABLE detalles_consulta_medicos (
    ID SMALLSERIAL,
    IDC INT,
    IDM INT,
    CONSTRAINT fk_detalles_consulta_consulta_id FOREIGN KEY (IDC)
        REFERENCES consultas (ID) ON UPDATE RESTRICT ON DELETE RESTRICT,
    CONSTRAINT fk_detalles_consulta_medicos_medicamentos_id FOREIGN KEY (IDM)
        REFERENCES medicamentos (ID) ON UPDATE RESTRICT ON DELETE RESTRICT,
    CONSTRAINT pk_detalles_consulta_medicos_id PRIMARY KEY(ID, IDC, IDM)
); 

INSERT INTO detalles_consulta_medicos VALUES (1, 1, 1), (2, 1, 2), (3, 2, 5), (4, 2, 6), (5, 3, 11), (6, 3, 12), (7, 4, 17), (8, 4, 18), (9, 4, 19), (10, 5, 23), (11, 5, 22);

CREATE TABLE especialidad_medicos (
    ID SMALLSERIAL,
    IDM INT,
    IDE INT,
    CONSTRAINT pk_especialidad_medicos_id PRIMARY KEY (ID),
    CONSTRAINT fk_especialidad_medicos_medicos_id FOREIGN KEY (IDM)
        REFERENCES medicos (ID) ON UPDATE RESTRICT ON DELETE RESTRICT
);

INSERT INTO especialidad_medicos VALUES (1, 1, 1), (2, 2, 2), (3, 3, 3), (4, 4, 4), (5, 5, 5);

CREATE TABLE administradores (
    ID SMALLSERIAL,
    usuario CHARACTER VARYING(20),
    contra CHARACTER VARYING(32),

    CONSTRAINT pk_administradores_id PRIMARY KEY (id)
);

INSERT INTO administradores (usuario, contra) VALUES ('root', ENCRYPT('1234', 'llave', '3des')::TEXT);

INSERT INTO administradores (usuario, contra) VALUES ('root', md5('1234'));

-- 

CREATE OR REPLACE FUNCTION autenticacion (_usuario CHARACTER VARYING, _contra CHARACTER VARYING)
RETURNS TABLE (usario CHARACTER VARYING)
AS
$BODY$

    BEGIN

        RETURN QUERY SELECT usuario FROM administradores WHERE usuario = _usuario AND
                contra = md5(_contra);

    END;

$BODY$
LANGUAGE plpgsql;

/* FUNCION DES PACIENTES */
CREATE OR REPLACE FUNCTION consulta_pacientes(_limite CHARACTER VARYING, _pagina CHARACTER VARYING)
RETURNS SETOF pacientes AS
$BODY$
    DECLARE
        inicio INT;
    BEGIN
        inicio = _limite::INT * _pagina::INT - _limite::INT;
        RETURN QUERY SELECT id, nombre, apellidop, apellidom, sexo, edad, telefono, calle, numero, ciudad 
                     FROM pacientes ORDER BY nombre
                     LIMIT _limite::INT OFFSET inicio;
                    
    END;
$BODY$
LANGUAGE plpgsql;
SELECT consulta_pacientes('10', '2');

/* FUNCION DE MEDICOS */
CREATE OR REPLACE FUNCTION consulta_medicos(_limite CHARACTER VARYING, _pagina CHARACTER VARYING)
RETURNS TABLE (
    id SMALLINT,
    nombre CHARACTER VARYING,
    apellidop CHARACTER VARYING,
    apellidom CHARACTER VARYING,
    sexo CHARACTER VARYING,
    edad INT,
    telefono CHARACTER VARYING,
    especialidad CHARACTER VARYING
) AS
$BODY$
    DECLARE
        inicio INT;
    BEGIN
        inicio = _limite::INT * _pagina::INT - _limite::INT;

        RETURN QUERY SELECT m.id, m.nombre, m.apellidop, m.apellidom, m.sexo, m.edad, m.telefono, e.especialidad
        FROM medicos AS m
        INNER JOIN especialidad AS e
        ON m.id = e.id
        LIMIT _limite::INT OFFSET inicio;
        
    END;
$BODY$
LANGUAGE plpgsql;

/* FUNCION DE CONSULTAS */
CREATE OR REPLACE FUNCTION consulta_consultas(_limite CHARACTER VARYING, _pagina CHARACTER VARYING)
RETURNS SETOF consultas AS
$BODY$
    DECLARE
        inicio INT;
    BEGIN
        inicio = _limite::INT * _pagina::INT - _limite::INT;
        RETURN QUERY SELECT id, idp, idm, fecha FROM consultas ORDER BY fecha
        LIMIT _limite::INT OFFSET inicio;
    END;
$BODY$
LANGUAGE plpgsql;

/* FUNCION DE INSERCION */
/* FUNCION INSERCION pacientes */
CREATE OR REPLACE FUNCTION pacientes (
    _nombre CHARACTER VARYING,
    _apellidop CHARACTER VARYING,
    _apellidom CHARACTER VARYING,
    _sexo CHARACTER VARYING,
    _edad CHARACTER VARYING,
    _telefono CHARACTER VARYING,
    _calle CHARACTER VARYING,
    _numero CHARACTER VARYING,
    _ciudad CHARACTER VARYING
) RETURNS VOID AS
$BODY$
    
    BEGIN
        INSERT INTO pacientes (nombre, apellidop, apellidom, sexo, edad, telefono, calle, numero, ciudad) 
        VALUES (_nombre, _apellidop, _apellidom, _sexo, _edad::INT, _telefono, _calle, _numero::INT, _ciudad);
    END;

$BODY$
LANGUAGE plpgsql;

SELECT pacientes ('Isidro', 'Bravo', 'Ubieta', 'H', '39', '7162938454', 'Zaragoza', '1010', 'Tuxtepec');

CREATE OR REPLACE FUNCTION medicos (
    _nombre CHARACTER VARYING,
    _apellidop CHARACTER VARYING,
    _apellidom CHARACTER VARYING,
    _sexo CHARACTER VARYING,
    _edad CHARACTER VARYING,
    _telefono CHARACTER VARYING,
    _especialidad CHARACTER VARYING
) RETURNS VOID AS
$BODY$

    BEGIN
        INSERT INTO medicos (nombre, apellidop, apellidom, sexo, edad, telefono, especialidad)   
        VALUES (_nombre, _apellidop, _apellidom, _sexo, _edad::INT, _telefono, _especialidad);
    END;

$BODY$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION consultas (
    _idp CHARACTER VARYING,
    _idm CHARACTER VARYING
) RETURNS VOID AS
$BODY$

    BEGIN
        INSERT INTO consultas (idp, idm)
        VALUES (_idp::INT, _idm::INT);
    END;

$BODY$
LANGUAGE plpgsql;

-- Consulta donde muestre las consultas del paciente x
-- CONSULTAS ANTERIORES 
SELECT c.id, c.idp, c.idm
    , p.nombre AS nombrepaciente
    , p.apellidop AS apellidompaciente
    , p.apellidom AS apellidoppaciente
    , m.nombre AS nombremedico
    , m.apellidop AS apellidopmedico
    , m.apellidom AS apellidommedico
    , c.fecha
FROM consultas AS c
INNER JOIN pacientes AS p
ON c.idp = p.id
INNER JOIN medicos AS m
ON c.idm = m.id
WHERE c.idp = 1;



CREATE OR REPLACE FUNCTION consultas_paciente (_IDP CHARACTER VARYING)
RETURNS TABLE (id SMALLINT, idp INT, idm INT, nombrepaciente CHARACTER VARYING
             , apellidompaciente CHARACTER VARYING, apellidoppaciente CHARACTER VARYING
             , nombremedico CHARACTER VARYING, apellidopmedico CHARACTER VARYING
             , apellidommedico CHARACTER VARYING, fecha DATE)
AS
$BODY$
    
    BEGIN
        RETURN QUERY SELECT c.id, c.idp, c.idm
                        , p.nombre AS nombrepaciente
                        , p.apellidop AS apellidompaciente
                        , p.apellidom AS apellidoppaciente
                        , m.nombre AS nombremedico
                        , m.apellidop AS apellidopmedico
                        , m.apellidom AS apellidommedico
                        , c.fecha
                    FROM consultas AS c
                    INNER JOIN pacientes AS p
                    ON c.idp = p.id
                    INNER JOIN medicos AS m
                    ON c.idm = m.id
                    WHERE c.idp = _IDP::INT;
   END;
$BODY$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION consultas_medico (_IDP CHARACTER VARYING)
RETURNS TABLE (id SMALLINT, idp INT, idm INT, nombrepaciente CHARACTER VARYING
             , apellidompaciente CHARACTER VARYING, apellidoppaciente CHARACTER VARYING
             , nombremedico CHARACTER VARYING, apellidopmedico CHARACTER VARYING
             , apellidommedico CHARACTER VARYING, fecha DATE)
AS
$BODY$

    BEGIN
        RETURN QUERY SELECT c.id, c.idp, c.idm
                        , p.nombre AS nombrepaciente
                        , p.apellidop AS apellidompaciente
                        , p.apellidom AS apellidoppaciente
                        , m.nombre AS nombremedico
                        , m.apellidop AS apellidopmedico
                        , m.apellidom AS apellidommedico
                        , c.fecha
                    FROM consultas AS c
                    INNER JOIN pacientes AS p
                    ON c.idp = p.id
                    INNER JOIN medicos AS m
                    ON c.idm = m.id
                    WHERE c.idm = _IDP::INT;
   END;
$BODY$
LANGUAGE plpgsql;


SELECT c.id, c.idp, c.idm
                        , p.nombre AS nombrepaciente
                        , p.apellidop AS apellidompaciente
                        , p.apellidom AS apellidoppaciente
                        , m.nombre AS nombremedico
                        , m.apellidop AS apellidopmedico
                        , m.apellidom AS apellidommedico
                        , c.fecha
                    FROM consultas AS c
                    INNER JOIN pacientes AS p
                    ON c.idp = p.id
                    INNER JOIN medicos AS m
                    ON c.idm = m.id
                    WHERE c.idm = 1;

SELECT m.id, m.nombre, m.apellidop, m.apellidom, m.sexo, m.edad, m.telefono, e.especialidad
FROM medicos AS m
INNER JOIN especialidad AS e
ON m.id = e.id;






