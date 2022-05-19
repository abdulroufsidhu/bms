CREATE TABLE emails (
	id BIGSERIAL PRIMARY KEY,
	data VARCHAR(250) NOT NULL UNIQUE
);

CREATE TABLE contacts (
	id BIGSERIAL PRIMARY KEY,
	data VARCHAR(250) NOT NULL UNIQUE
);

CREATE TABLE national_identity_card_numbers (
	id BIGSERIAL PRIMARY KEY,
	data VARCHAR(250) NOT NULL UNIQUE
);

CREATE TABLE countries (
	id BIGSERIAL PRIMARY KEY,
	name VARCHAR(250) NOT NULL UNIQUE,
	code NUMERIC(3) NOT NULL,
	currency VARCHAR(3) NOT NULL,
	currency_symbol VARCHAR(3) NOT NULL
);

CREATE TABLE cities (
	id BIGSERIAL PRIMARY KEY,
	name VARCHAR(250) NOT NULL,
	zip_code VARCHAR(8) NOT NULL,
	country_id BIGINT REFERENCES countries(id)
);

CREATE TABLE addresses (
	id BIGSERIAL PRIMARY KEY,
	country_id BIGINT REFERENCES countries(id),
	city_id BIGING REFERENCES cities(id),
	street VARCHAR(300) NOT NULL
);

CREATE TABLE person_names (
	id BIGSERIAL PRIMARY KEY,
	name VARCHAR(250) UNIQUE
); 

CREATE TABLE users (
	id BIGSERIAL PRIMARY KEY,
	person_name_id BIGSERIAL REFERENCES person_names(id),
	age NUMERIC(3) NOT NULL,
	address_id BIGINT REFERENCES addresses(id),
	email_id BIGINT REFERENCES emails(id),
	contact_id BIGINT REFERENCES contacts(id),
	nationality_identity_card_number_id BIGINT REFERENCES nationality_identity_card_numbers(id)
);

CREATE TABLE businesses (
	id BIGSERIAL PRIMARY KEY,
	name VARCHAR (250) NOT NULL UNIQUE,
	address_id BIGINT REFERENCES addresses(id),
	email_id BIGINT REFERENCES emails(id),
	contact_id BIGINT REFERENCES contacts(id)
);

CREATE TABLE branch (
	id BIGSERIAL PRIMARY KEY,
	name VARCHAR (250) NOT NULL UNIQUE,
	address_id BIGINT REFERENCES addresses(id),
	email_id BIGINT REFERENCES emails(id),
	contact_id BIGINT REFERENCES contacts(id)
);

CREATE TABLE job_names (
	id BIGSERIAL PRIMARY KEY,
	name VARCHAR(250) NOT NULL UNIQUE
);

CREATE TABLE companies_names (
	id BIGSERIAL PRIMARY KEY,
	name VARCHAR(250) UNIQUE,
);

CREATE TABLE item_names (
	name VARCHAR(250) UNIQUE
);

CREATE TABLE items (
	id BIGSERIAL PRIMARY KEY,
	item_name_id BIGINT REFERENCES item_name(id),
	company_name_id BIGINT REFERENCES companies_names(id),
	specifications JSON
);

CREATE TABLE prices (
	id BIGSERIAL PRIMARY KEY,
	prices JSON NOT NULL,
)

CREATE TABLE inventory (
	id BIGSERIAL PRIMARY KEY,
	item_id BIGSERIAL REFERENCES items(id),
	price_id
);
















