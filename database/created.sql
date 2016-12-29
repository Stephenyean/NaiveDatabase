DROP DATABASE orderDB;
CREATE DATABASE orderDB;

USE orderDB;

CREATE TABLE publisher (
  id int(10) NOT NULL,
  name char(100) NOT NULL,
  state char(2),
  PRIMARY KEY  (id)
);

CREATE TABLE book (
  id int(10) NOT NULL,
  title varchar(100) NOT NULL,
  authors varchar(200),
  publisher_id int(10) NOT NULL,
  copies int(10),
  pages int(10),
  PRIMARY KEY  (id)
);

CREATE TABLE customer (
  id int(10) NOT NULL,
  name char(25) NOT NULL,
  gender char(1) NOT NULL,
  CHECK (gender in('F','M')),
  PRIMARY KEY (id)
);

CREATE TABLE orders (
  customer_id int(10) NOT NULL,
  book_id int(10) NOT NULL,
  quantity int(10) NOT NULL
);

INSERT INTO book VALUES 
 (200001,'Marias Diary (Plus S.)','Mark P. O. Morford',100082,5991,2530),
 (200002,'Standing in the Shadows','Anthony Boucher',101787,2900,1860),
 (200003,'Children of the Thunder','Carlo DEste',102928,3447,2154),
 (200004,'The Great Gilly Hopkins','Gina Bari Kolata',101339,39,2809),
 (200005,'Meine Juden--eure Juden','E. J. W. Barber',103089,206,2771),
 (200006,'You Can Draw a Kangaroo','Amy Tan',101850,5296,2092),
 (200007,'The Little Drummer Girl','Robert Cowley',104382,1006,2764),
 (200008,'A Walk Through the Fire','Scott Turow',102008,8795,2543),
 (200009,'The Nursing Home Murder','David Cordingly',102866,7380,2019),
 (200010,'The Blanket of the Dark','Ann Beattie',103933,5242,1483),
 (200011,'Not Without My Daughter','David Adams Richards',101177,567,1851),
 (200012,'Introducing Halle Berry','Adam Lebor',104762,3505,1040),
 (200013,'Men Who Love Too Little','Sheila Heti',103084,6131,2770),
 (200014,'Once In a House On Fire','R. J. Kaiser',104024,4472,2876),
 (200015,'Skindeep (Pan Horizons)','Jack Canfield',100670,4898,2729),
 (200016,'A Voice Through a Cloud','Loren D. Estleman',101508,8322,1171),
 (200017,'Master Georgie: A Novel','Robert Hendrickson',102615,1448,2716),
 (200018,'Verdun (Lost Treasures)','Julia Oliver',102598,7459,1430),
 (200019,'Der Pferdefl??sterer.','John Grisham',103834,6335,2303),
 (200020,'Snowboarding to Nirvana','Toni Morrison',101085,8670,1524),
 (200021,'Boys and Girls Together','The Onion',102228,3546,1375);

 INSERT INTO book VALUES (200001,'Marias Diary (Plus S.)','Mark P. O. Morford',100082,5991,2530);