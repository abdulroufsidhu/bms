CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

create table contacts (
id uuid default uuid_generate_v4() primary key
, contact text not null unique
);

create table cnics (
id uuid default uuid_generate_v4() primary key
, cnic text not null unique
);

create table emails (
id uuid default uuid_generate_v4() primary key
, email text not null unique
);

create table auth (
id uuid default uuid_generate_v4() primary key
, password text not null
, emailid uuid references emails(id) 
, active boolean default true not null
);


create table jobs (
id uuid default uuid_generate_v4() primary key
, designation text not null unique
, grade integer not null
);

create table locations (
id uuid default uuid_generate_v4() primary key
, city text 
, country text 
, address text
);

create table persons (
id uuid default uuid_generate_v4() primary key
, emailid uuid references emails(id) unique
, contactid uuid references contacts(id) unique
, cnicid uuid references cnics(id) unique
, locationid uuid references locations(id)
, name text not null 
);

create table organizations (
id uuid default uuid_generate_v4() primary key
, name text not null
, founderid uuid references persons(id) text not null
, emailid uuid references emails(id) not null unique --yet to be added in database // November 7, 2021  10:13am
-- , logo 	//yet to implement
);

create table branches (
id uuid default uuid_generate_v4() primary key
, name text
, locationid uuid References locations(id) not null
, organizationid uuid not null references organizations (id)
, contactid uuid references contacts(id) 
, emailid uuid references emails(id) not null unique --yet to be added in database // Novmber 7, 2021 10:13am
);

create table users (
id uuid default uuid_generate_v4() primary key
, personid uuid references persons(id) unique
, jobid uuid references jobs(id)
, branchid uuid references branches(id)
, salary
);

create table itemtypes (
id uuid default uuid_generate_v4() primary key
, itemtype text not null
);

create table items (
id uuid default uuid_generate_v4() primary key
, itemtypeid uuid references itemtypes(id) not null
, company not null	
, name text not null
, modal text not null 	--yet to add in db //November 7, 2021 
, version text 		--yet to add in db //November 7, 2021 
, vendor text 		--yet to add in db //November 7, 2021 
);

create table inventory (
id uuid default uuid_generate_v4() primary key
, itemid uuid references items(id)
, attributes text not null
, colour text not null
, serial text
, branchid uuid references branches(id)
, quantity numeric not null default 1
, price numeric not null
--, code text not null 
);

create table deals (
id uuid default uuid_generate_v4() primary key
, inventoryid uuid references inventory(id)
, price numeric not null
, discount numeric default 0
, personid uuid references persons(id) not null              
, userid uuid references users(id) not null
, quantity integer default 1
, branchid uuid references branches(id) not null
, profit
, time date not null default CURRENT_DATE -- to use it I can say select to_char(time,'yyyymm') from deals
);

create table expensis (
id uuid default uuid_generate_v4() primary key
, branchid uuid references branches(id) not null
, reason text not null
, expense numeric not null
, time date not null default CURRENT_DATE
);

create table reports (
id uuid default uuid_generate_v4() primary key
, branchid uuid references branches(id) not null
, profit numeric not null default 0
, time date not null default CURRENT_DATE
);

/*
create table employees (
id uuid default uuid_generate_v4() primary key
, jobid uuid references jobs(id) not null
, userid uuid references users(id) not null
, branchid uuid references branchs(id) not null
, salary numeric not null default 0
, active boolean default true
, joining date default now()
, resignation date
);
*/

/**
insert into contacts (id, contact) values (uuid_generate_v4(), '03042816024');
insert into contacts (id, contact) values (uuid_generate_v4(),'03087968322');
insert into contacts (contact) values ('03016105399');
insert into cnics (cnic) values ('3120218954763');
insert into cnics (cnic) values ('3120202883216');
insert into emails (email) values ('abdulroufsidhu@gmail.com');
insert into emails (email) values ('example@example.com');
insert into jobs (designation, grade) values ('sales man', 3);
insert into jobs (designation, grade) values ('chief',22);
insert into jobs (designation, grade) values ('ceo',21);
insert into locations (city, country, address) values ('bahawalpur', 'pakista      n', 'nazirabad colony');
insert into locations (city, country, address) values ('bahawalpur', 'pakistan', 'nazirabad colony near bindrapulli');
insert into organizations (name, founder) values ('open solutions', 'abdul rauf');
insert into organizations (name, founder) values ('open organization', 'abdul rauf');
insert into branchs (name, lid, oid) select 'code lab' ,locations.id, organizations.id from locations, organizations where locations.city = 'bahawalpur' and locations.country = 'pakistan' and locations.address = 'nazirabad colony' and organizations.name = 'open solutions' and organizations.founder = 'abdul rauf';
insert into persons (name, emailid, contactid, cnicid,locationid) select 'abdul rauf', emails.id, contacts.id , cnics.id, locations.id from emails, contacts, cnics, locations where emails.email= 'example@example.com' and contacts.contact = '03087968322' and cnics.cnic = '3120202883216' and locations.city = 'bahawalpur' and locations.country = 'pakistan' and locations.address = 'nazirabad colony';
select persons.name, emails.email, cnics.cnic, contacts.contact, locations.city, locations.country, locations.address from persons inner join emails on (emailid = emails.id) inner join cnics on (cnicid = cnics.id) inner join contacts on ( contactid = contacts.id ) inner join locations on (locationid = locations.id);
--insert into users (personid, branchid, jobid, salary, active) select persons.id, branchs.id, jobs.id, 5300.45, true from persons, branchs, jobs where persons.name = 'abdul rauf'  and branchs.name = 'code lab' and jobs.designation = 'chief' and jobs.grade = 22;
**/




