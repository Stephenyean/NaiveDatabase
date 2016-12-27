read file created;
USE orderDB;
show table book;
select * from book;
select * from book where authors > 'Mark';
UPDATE book SET title='Nine Times Nine' WHERE authors='Anthony Boucher'; 
delete from book where authors > 'Mark';
delete from book where title like '%in%';
delete from book where id=200002;