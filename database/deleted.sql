read file created;
USE orderDB;
show table book;
select * from book;
delete from book where id > 200000 and title like '_ou%';
UPDATE book SET title='Nine Times Nine' WHERE authors='Laura J. Mixon'; 
select * from book;
select * from book WHERE authors='Anthony Boucher';


select * from book, customer WHERE book.id<200005 and customer.id<300005;

select * from book where authors > 'Mark';
delete from book where authors > 'Mark';
delete from book where id=200002;