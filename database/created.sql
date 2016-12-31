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
 (200002,'Standing in the Shadows','Richard Bruce Wright',101787,2900,1860),
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
 (200021,'Boys and Girls Together','The Onion',102228,3546,1375),
 (200022,'Another Century of War?','Celia Brooks Brown',101834,2502,2468),
 (200023,'A Book of Weather Clues','J. R. Parrish',100372,6066,2053),
 (200024,'The Klutz Strikes Again','Mary-Kate &amp; Ashley Olsen',100733,8831,2687),
 (200025,'Commitments (Arabesque)','Robynn Clairday',100289,2509,1827),
 (200026,'The Third Twin: A Novel','Kathleen Duey',102335,4515,1624),
 (200027,'The Dog Who Wouldnt Be','Rich Shapero',102789,6722,2581),
 (200028,'Destined for the Throne','Michael Crichton',102197,6842,2269),
 (200029,'Year of the Roasted Ear','C.S. Lewis',100428,8147,2981),
 (200030,'The Horned Man: A Novel','ARTHUR PHILLIPS',104445,97,1774),
 (200031,'Ensayo Sobre LA Ceguera','Stephan Jaramillo',100528,8844,2441),
 (200032,'Flying High (Arabesque)','Mordecai Richler',103321,3338,1844),
 (200033,'Du entkommst mir nicht.','Eleanor Cooney',102133,3913,1433),
 (200034,'Keeping Faith : A Novel','Charlotte Link',100765,1018,2554),
 (200035,'The Gift for All People','Richard North Patterson',104940,4918,1573),
 (200036,'Deer &amp; deer hunting','Mark Salzman',104582,3657,2549),
 (200037,'Trust in Me (Arabesque)','Harper Lee',102886,8015,2077),
 (200038,'Gotham Diaries: A Novel','LAURA HILLENBRAND',102273,8397,1449),
 (200039,'The Book of the Unicorn','Barbara Kingsolver',101182,5168,1706),
 (200040,'The Multicultiboho Show','Jo Dereske',100901,7885,1141),
 (200041,'Le Poulpe : Zarmageddon','Jane Austen',104804,8188,2818),
 (200042,'Trials of Tiffany Trott','Dolores Krieger',101887,7012,1420),
 (200043,'Bob Knight: His Own Man','Anne Rivers Siddons',100146,1426,2457),
 (200044,'The Mediterranean Caper','Dean R. Koontz',102144,5405,1547),
 (200045,'A Dictionary of Symbols','Mary Higgins Clark',103812,7116,1273),
 (200046,'The Ghost and Mrs. Muir','Dean Koontz',101637,8830,1048),
 (200047,'The Well (King Penguin)','Patricia Cornwell',100657,418,1827),
 (200048,'Without a Hero: Stories','J.D. Robb',100882,2869,1029),
 (200049,'Speaking With Strangers','Maeve Binchy',103744,4551,1007),
 (200050,'101 Uses for a Dead Cat','Laura J. Mixon',103539,1492,2321),
 (200051,'The Knight and the Rose','Tim Lahaye',103425,2928,2350),
 (200052,'Departures and Arrivals','M.D. Bernie S. Siegel',101545,6307,2797),
 (200053,'The Book of the Dun Cow','Robert Penn Warren',102114,9314,2923),
 (200054,'Neils Book of the Dead','Hans Johannes Hoefer',101686,4319,1528),
 (200055,'A Secret Word : A Novel','Mark Helprin',104282,1330,1268),
 (200056,'Tabloid Dreams: Stories','O. Carol Simonton Md',103277,8482,1220),
 (200057,'The Truth About Forever','Chuck Hill',104086,9723,2829),
 (200058,'Death of Expert Witness','David Iglehart',101721,359,1403),
 (200059,'A Garden for Miss Mouse','Larry McMurtry',102973,5852,2697),
 (200060,'Dress You Up in My Love','SUZANNE FISHER STAPLES',102016,2732,2734),
 (200061,'Night Journey : A Novel','Michel Tournier',101049,2921,1890),
 (200062,'Modern American Memoirs','Carl Sagan',104651,8306,1114),
 (200063,'Gone, but Not Forgotten','Aleksandr Zinoviev',104093,4024,1387),
 (200064,'A Manhattan Ghost Story','Anne Tyler',104581,3526,2277),
 (200065,'The Lords of Discipline','Joseph Conrad',100246,3036,2375),
 (200066,'Beetles Lightly Toasted','Deepak Chopra',102797,7169,2252),
 (200067,'The Horror Hall of Fame','Thomas Hardy',104479,1810,1682),
 (200068,'Milkrun (Red Dress Ink)','Charles Noland',100586,7749,2642),
 (200069,'Once Upon a Potty : His','Valerie Frankel',102845,2083,1511),
 (200070,'Voyage: A Novel of 1896','Benjamin Hoff',100835,5554,2363),
 (200071,'The Fairest Among Women','Niccolo Machiavelli',101291,5001,2862),
 (200072,'Win Strk Schol: Lisa PB','H. Jackson Brown',101104,5446,1713),
 (200073,'How to talk to your cat','Robert A. Heinlein',101555,4077,2765),
 (200074,'Home Buying for Dummies','PHILIP PULLMAN',103656,3545,2885),
 (200075,'The Cat Who...Companion','Anna Sewell',103946,5574,2134),
 (200076,'A Manhattan Ghost Story','MICHAEL ONDAATJE',102039,3218,1375),
 (200077,'The Revelation: A Novel','Sandra Levy Ceren',100607,3778,2957),
 (200078,'Shadows (Smallville #5)','P.J. ORourke',101628,4033,2380),
 (200079,'Playgrounds of the Mind','Mike Gayle',100288,8121,2330),
 (200080,'Escape from the Kitchen','Stel Pavlou',104317,8336,2266),
 (200081,'Master Georgie: A Novel','Sarah Payne Stuart',100280,6938,1645),
 (200082,'Infancia de Un Jefe, La','Dan Quayle',103599,1786,1592),
 (200083,'Panther in the Basement','Donald F. Kettl',104937,6136,1558),
 (200084,'Nicholas at the Library','DAVID FRUM',101238,8860,2148),
 (200085,'Auf Gedeih und Verderb.','Louis Lamour',101698,6095,1655),
 (200086,'Object Lessons: A Novel','J.D. Salinger',103260,9806,1270),
 (200087,'Les bruines de Lanester','J. R. R. Tolkien',100645,7318,1708),
 (200088,'A House for Hermit Crab','John Berendt',102706,2005,1333),
 (200089,'All the Sweet Tomorrows','Jennifer Crusie',103624,4066,2210),
 (200090,'1000 Forbidden Pictures','Jane Heller',104329,6966,2990),
 (200091,'T??dliche Versuchung.','Michael Rips',102533,6794,2538),
 (200092,'A Suitable Boy: A Novel','Simon Mawer',100299,6228,1847),
 (200093,'Arthur: King of Britain','William Abrahams',101328,1533,2030),
 (200094,'Autumn of the Patriarch','Robert T. Kiyosaki',100707,8673,2577),
 (200095,'Canapes for the Kitties','Ken Follett',103093,1446,1444),
 (200096,'Diet for a Small Planet','John F. Love',103158,6576,2427),
 (200097,'Beneath a Midnight Moon','Robert G. Allen',104252,5814,1742),
 (200098,'Deadlines and Datelines','LOUIS DE BERNIERES',101756,8459,1592),
 (200099,'Gulac War (Sobs, No 6)','Pam Proctor',100546,9538,2544),
 (200100,'Anyone Can Have a Happy',null,103343,3358,2213);

select * from book;

 INSERT INTO book VALUES (200001,'Marias Diary (Plus S.)','Mark P. O. Morford',100082,5991,2530);

show table customer;
INSERT INTO customer VALUES (123, 'Alice', 'F');
INSERT INTO customer VALUES (125, 'BOB', 'FM');