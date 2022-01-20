-- installing uuid extension
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- creating coutires table
CREATE TABLE IF NOT EXISTS COUNTRIES (
  id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
  iso char(2) NOT NULL,
  name varchar(80) NOT NULL UNIQUE,
  nicename varchar(80) NOT NULL UNIQUE,
  iso3 char(3) DEFAULT NULL UNIQUE,            
  numcode NUMERIC(6,0) DEFAULT NULL ,
  phonecode NUMERIC(5,0) NOT NULL 
);

-- creating cities table
CREATE TABLE IF NOT EXISTS CITIES (
  id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
  country_id UUID NOT NULL REFERENCES COUNTRIES (id),
  name varchar(90),
  UNIQUE ( country_id, name )
);

-- creating locations table
CREATE TABLE IF NOT EXISTS LOCATIONS (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
  city_id UUID REFERENCES CITIES(id),
  name varchar(150),
  UNIQUE (city_id, name)
);

-- creating contacts table
CREATE TABLE IF NOT EXISTS CONTACTS (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
  name VARCHAR(16) UNIQUE NOT NULL
);

-- creating emails table
CREATE TABLE IF NOT EXISTS EMAILS (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
  name varchar(150) UNIQUE,
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating cnics table
CREATE TABLE IF NOT EXISTS CNICS (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	name char(13) UNIQUE,
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating persons table
CREATE TABLE IF NOT EXISTS PERSONS (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	name varchar(150),
	temp_residence_id UUID REFERENCES LOCATIONS(id) NOT NULL,
	parm_residence_id UUID REFERENCES LOCATIONS (id) NOT NULL,
	email_id UUID REFERENCES EMAILS(id) NOT NULL UNIQUE,
	cnic_id UUID REFERENCES CNICS(id) NOT NULL UNIQUE,
	contact_id UUID REFERENCES CONTACTS(id) NOT NULL UNIQUE,
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating users table
CREATE TABLE IF NOT EXISTS USERS (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	person_id UUID REFERENCES PERSONS (id) not null UNIQUE,
	password VARCHAR (150) NOT NULL,
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
); 

CREATE TABLE IF NOT EXISTS IMAGES (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	data BYTEA NOT NULL,
	owmer_id VARCHAR(40) not null, -- cannot have unique or refrence because they could vary based on user organization or task soo whoever owns it is different.
	time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);


--IMAGE TABLE which will be replaced with img_user_id, img_organizatio_id respectively
--CREATE TABLE IF NOT EXISTS IMG (
--	image BYTEA,
--	time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
--);

-- creating organizations table
CREATE TABLE IF NOT EXISTS ORGANIZATIONS (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	name varchar(150) UNIQUE,
	contact_id UUID REFERENCES CONTACTS(id) NOT NULL UNIQUE,
	email_id UUID REFERENCES EMAILS(id) NOT NULL UNIQUE,
	location_id UUID REFERENCES LOCATIONS(id) NOT NULL,
	gov_reg_num varchar(13),
	active BOOLEAN NOT NULL DEFAULT TRUE,
	expiry TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT 'now'::timestamp + '1 month'::interval,
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating branches table
CREATE TABLE IF NOT EXISTS BRANCHES /*will be dynamicaaly created by organization as branches_organization_id*/ (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	contact_id UUID REFERENCES CONTACTS (id) NOT NULL UNIQUE,
	email_id UUID REFERENCES EMAILS(id) NOT NULL UNIQUE,
	organization_id UUID REFERENCES ORGANIZATIONS (id) NOT NULL ,
	name varchar(150) NOT NULL,
	code varchar(13) NOT NULL,
	UNIQUE (organization_id, name, code),
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating jobs table
CREATE TABLE IF NOT EXISTS JOBS (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	name varchar(150) UNIQUE,
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating currency table
CREATE TABLE IF NOT EXISTS CURRENCY (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	name varchar(30),
	code char(3),
	symbol char(5),
	UNIQUE (name, code, symbol) 
);

-- creating employees table
CREATE TABLE IF NOT EXISTS EMPLOYEES /*will be dynamically created by organization as employees_organization_id*/ (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	user_id UUID REFERENCES USERS(id) NOT NULL,
	branch_id UUID REFERENCES BRANCHES(id) NOT NULL,
	job_id UUID REFERENCES JOBS (id) NOT NULL,
	salary NUMERIC NOT NULL DEFAULT 0,
	currency_id UUID REFERENCES CURRENCY (id) NOT NULL,
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating permissions table
CREATE TABLE IF NOT EXISTS PERMISSIONS --permissions_organization_id 
(
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	employee_id UUID REFERENCES EMPLOYEES(id) NOT NULL,
	super_admin BOOLEAN DEFAULT TRUE NOT NULL,
	admin BOOLEAN DEFAULT FALSE NOT NULL,
	login BOOLEAN DEFAULT TRUE NOT NULL,
	read_branches BOOLEAN DEFAULT TRUE NOT NULL,
	add_branches BOOLEAN DEFAULT TRUE NOT NULL,
	remove_branches BOOLEAN DEFAULT TRUE NOT NULL,
	hire_employees BOOLEAN DEFAULT TRUE NOT NULL,
	fire_employees BOOLEAN DEFAULT TRUE NOT NULL,
	add_products BOOLEAN DEFAULT TRUE NOT NULL,
	remove_products BOOLEAN DEFAULT TRUE NOT NULL,
	update_products BOOLEAN DEFAULT TRUE NOT NULL,
	sell_products BOOLEAN DEFAULT TRUE NOT NULL,
	search_products BOOLEAN DEFAULT TRUE NOT NULL,
	delete_records BOOLEAN DEFAULT TRUE NOT NULL
);

-- creating logs table
CREATE TABLE IF NOT EXISTS LOGS -- will be dynamically created by logs_organization_employee_id and contain every operation's details
(
	operation varchar(150) NOT NULL,
  time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating inventory table
CREATE TABLE IF NOT EXISTS INVENTORY (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	name varchar(60) ,
	company varchar(60),
	seial_key varchar(20),
	vendor varchar(60),
	specs varchar(500),
	quantity integer NOT NULL DEFAULT 0,
	unit_price NUMERIC NOT NULL DEFAULT 0,
	branch_id UUID REFERENCES BRANCHES(id) NOT NULL,
	time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

/*
-- function which triggers at every select transaction and delete all the rows with 0 quantity in inventory
CREATE FUNCTION delete_inventory_with_no_qty_available() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
  DELETE FROM INVENTORY WHERE quantity < 1;
  RETURN NEW;
END;
$$;
-- attaching trigger to inventory
CREATE TRIGGER delet_inventory_with_no_qty_available_trigger
    AFTER SELECT ON INVENTORY
    EXECUTE PROCEDURE delete_inventory_with_no_qty_available();
*/

-- types of customer organization deals with e.g whole sale, retail, walk_in
CREATE TABLE IF NOT EXISTS CUSTOMERS_TYPES -- will be dynamically created as customer_types_organization_id
(
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	name varchar(20) NOT NULL,
	time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating customer specific one click pricing 
CREATE TABLE IF NOT EXISTS PRICES -- will be dynamically created as price_organization
(
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	inventory_id UUID REFERENCES INVENTORY(id),
	type UUID REFERENCES CUSTOMERS_TYPES (id),
	price NUMERIC NOT NULL DEFAULT 0,
	time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- creating sold table
CREATE TABLE IF NOT EXISTS SOLD (
	id UUID DEFAULT uuid_generate_v4() PRIMARY KEY,
	inventory_id UUID REFERENCES INVENTORY(id) ,
	specs varchar(500),
	quantity INTEGER NOT NULL DEFAULT 1,
	price_id UUID REFERENCES PRICES (id) NOT NULL,
	salesman UUID REFERENCES EMPLOYEES(id) NOT NULL,
	contact_id UUID REFERENCES CONTACTS(id),
	cnic_id UUID REFERENCES CNICS(id),
	buyer varchar(20),
	time_stamp TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL
);













-- countries list

INSERT INTO COUNTRIES (iso, name, nicename, iso3, numcode, phonecode) VALUES
('AF', 'AFGHANISTAN', 'Afghanistan', 'AFG', 4, 93),
('AL', 'ALBANIA', 'Albania', 'ALB', 8, 355),
('DZ', 'ALGERIA', 'Algeria', 'DZA', 12, 213),
('AS', 'AMERICAN SAMOA', 'American Samoa', 'ASM', 16, 1684),
('AD', 'ANDORRA', 'Andorra', 'AND', 20, 376),
('AO', 'ANGOLA', 'Angola', 'AGO', 24, 244),
('AI', 'ANGUILLA', 'Anguilla', 'AIA', 660, 1264),
('AQ', 'ANTARCTICA', 'Antarctica', NULL, NULL, 0),
('AG', 'ANTIGUA AND BARBUDA', 'Antigua and Barbuda', 'ATG', 28, 1268),
('AR', 'ARGENTINA', 'Argentina', 'ARG', 32, 54),
('AM', 'ARMENIA', 'Armenia', 'ARM', 51, 374),
('AW', 'ARUBA', 'Aruba', 'ABW', 533, 297),
('AU', 'AUSTRALIA', 'Australia', 'AUS', 36, 61),
('AT', 'AUSTRIA', 'Austria', 'AUT', 40, 43),
('AZ', 'AZERBAIJAN', 'Azerbaijan', 'AZE', 31, 994),
('BS', 'BAHAMAS', 'Bahamas', 'BHS', 44, 1242),
('BH', 'BAHRAIN', 'Bahrain', 'BHR', 48, 973),
('BD', 'BANGLADESH', 'Bangladesh', 'BGD', 50, 880),
('BB', 'BARBADOS', 'Barbados', 'BRB', 52, 1246),
('BY', 'BELARUS', 'Belarus', 'BLR', 112, 375),
('BE', 'BELGIUM', 'Belgium', 'BEL', 56, 32),
('BZ', 'BELIZE', 'Belize', 'BLZ', 84, 501),
('BJ', 'BENIN', 'Benin', 'BEN', 204, 229),
('BM', 'BERMUDA', 'Bermuda', 'BMU', 60, 1441),
('BT', 'BHUTAN', 'Bhutan', 'BTN', 64, 975),
('BO', 'BOLIVIA', 'Bolivia', 'BOL', 68, 591),
('BA', 'BOSNIA AND HERZEGOVINA', 'Bosnia and Herzegovina', 'BIH', 70, 387),
('BW', 'BOTSWANA', 'Botswana', 'BWA', 72, 267),
('BV', 'BOUVET ISLAND', 'Bouvet Island', NULL, NULL, 0),
('BR', 'BRAZIL', 'Brazil', 'BRA', 76, 55),
('IO', 'BRITISH INDIAN OCEAN TERRITORY', 'British Indian Ocean Territory', NULL, NULL, 246),
('BN', 'BRUNEI DARUSSALAM', 'Brunei Darussalam', 'BRN', 96, 673),
('BG', 'BULGARIA', 'Bulgaria', 'BGR', 100, 359),
('BF', 'BURKINA FASO', 'Burkina Faso', 'BFA', 854, 226),
('BI', 'BURUNDI', 'Burundi', 'BDI', 108, 257),
('KH', 'CAMBODIA', 'Cambodia', 'KHM', 116, 855),
('CM', 'CAMEROON', 'Cameroon', 'CMR', 120, 237),
('CA', 'CANADA', 'Canada', 'CAN', 124, 1),
('CV', 'CAPE VERDE', 'Cape Verde', 'CPV', 132, 238),
('KY', 'CAYMAN ISLANDS', 'Cayman Islands', 'CYM', 136, 1345),
('CF', 'CENTRAL AFRICAN REPUBLIC', 'Central African Republic', 'CAF', 140, 236),
('TD', 'CHAD', 'Chad', 'TCD', 148, 235),
('CL', 'CHILE', 'Chile', 'CHL', 152, 56),
('CN', 'CHINA', 'China', 'CHN', 156, 86),
('CX', 'CHRISTMAS ISLAND', 'Christmas Island', NULL, NULL, 61),
('CC', 'COCOS (KEELING) ISLANDS', 'Cocos (Keeling) Islands', NULL, NULL, 672),
('CO', 'COLOMBIA', 'Colombia', 'COL', 170, 57),
('KM', 'COMOROS', 'Comoros', 'COM', 174, 269),
('CG', 'CONGO', 'Congo', 'COG', 178, 242),
('CD', 'CONGO, THE DEMOCRATIC REPUBLIC OF THE', 'Congo, the Democratic Republic of the', 'COD', 180, 242),
('CK', 'COOK ISLANDS', 'Cook Islands', 'COK', 184, 682),
('CR', 'COSTA RICA', 'Costa Rica', 'CRI', 188, 506),
('CI', 'COTE D''IVOIRE', 'Cote D''Ivoire', 'CIV', 384, 225),
('HR', 'CROATIA', 'Croatia', 'HRV', 191, 385),
('CU', 'CUBA', 'Cuba', 'CUB', 192, 53),
('CY', 'CYPRUS', 'Cyprus', 'CYP', 196, 357),
('CZ', 'CZECH REPUBLIC', 'Czech Republic', 'CZE', 203, 420),
('DK', 'DENMARK', 'Denmark', 'DNK', 208, 45),
('DJ', 'DJIBOUTI', 'Djibouti', 'DJI', 262, 253),
('DM', 'DOMINICA', 'Dominica', 'DMA', 212, 1767),
('DO', 'DOMINICAN REPUBLIC', 'Dominican Republic', 'DOM', 214, 1809),
('EC', 'ECUADOR', 'Ecuador', 'ECU', 218, 593),
('EG', 'EGYPT', 'Egypt', 'EGY', 818, 20),
('SV', 'EL SALVADOR', 'El Salvador', 'SLV', 222, 503),
('GQ', 'EQUATORIAL GUINEA', 'Equatorial Guinea', 'GNQ', 226, 240),
('ER', 'ERITREA', 'Eritrea', 'ERI', 232, 291),
('EE', 'ESTONIA', 'Estonia', 'EST', 233, 372),
('ET', 'ETHIOPIA', 'Ethiopia', 'ETH', 231, 251),
('FK', 'FALKLAND ISLANDS (MALVINAS)', 'Falkland Islands (Malvinas)', 'FLK', 238, 500),
('FO', 'FAROE ISLANDS', 'Faroe Islands', 'FRO', 234, 298),
('FJ', 'FIJI', 'Fiji', 'FJI', 242, 679),
('FI', 'FINLAND', 'Finland', 'FIN', 246, 358),
('FR', 'FRANCE', 'France', 'FRA', 250, 33),
('GF', 'FRENCH GUIANA', 'French Guiana', 'GUF', 254, 594),
('PF', 'FRENCH POLYNESIA', 'French Polynesia', 'PYF', 258, 689),
('TF', 'FRENCH SOUTHERN TERRITORIES', 'French Southern Territories', NULL, NULL, 0),
('GA', 'GABON', 'Gabon', 'GAB', 266, 241),
('GM', 'GAMBIA', 'Gambia', 'GMB', 270, 220),
('GE', 'GEORGIA', 'Georgia', 'GEO', 268, 995),
('DE', 'GERMANY', 'Germany', 'DEU', 276, 49),
('GH', 'GHANA', 'Ghana', 'GHA', 288, 233),
('GI', 'GIBRALTAR', 'Gibraltar', 'GIB', 292, 350),
('GR', 'GREECE', 'Greece', 'GRC', 300, 30),
('GL', 'GREENLAND', 'Greenland', 'GRL', 304, 299),
('GD', 'GRENADA', 'Grenada', 'GRD', 308, 1473),
('GP', 'GUADELOUPE', 'Guadeloupe', 'GLP', 312, 590),
('GU', 'GUAM', 'Guam', 'GUM', 316, 1671),
('GT', 'GUATEMALA', 'Guatemala', 'GTM', 320, 502),
('GN', 'GUINEA', 'Guinea', 'GIN', 324, 224),
('GW', 'GUINEA-BISSAU', 'Guinea-Bissau', 'GNB', 624, 245),
('GY', 'GUYANA', 'Guyana', 'GUY', 328, 592),
('HT', 'HAITI', 'Haiti', 'HTI', 332, 509),
('HM', 'HEARD ISLAND AND MCDONALD ISLANDS', 'Heard Island and Mcdonald Islands', NULL, NULL, 0),
('VA', 'HOLY SEE (VATICAN CITY STATE)', 'Holy See (Vatican City State)', 'VAT', 336, 39),
('HN', 'HONDURAS', 'Honduras', 'HND', 340, 504),
('HK', 'HONG KONG', 'Hong Kong', 'HKG', 344, 852),
('HU', 'HUNGARY', 'Hungary', 'HUN', 348, 36),
('IS', 'ICELAND', 'Iceland', 'ISL', 352, 354),
('IN', 'INDIA', 'India', 'IND', 356, 91),
('ID', 'INDONESIA', 'Indonesia', 'IDN', 360, 62),
('IR', 'IRAN, ISLAMIC REPUBLIC OF', 'Iran, Islamic Republic of', 'IRN', 364, 98),
('IQ', 'IRAQ', 'Iraq', 'IRQ', 368, 964),
('IE', 'IRELAND', 'Ireland', 'IRL', 372, 353),
--('IL', 'ISRAEL', 'Israel', 'ISR', 376, 972),
('IT', 'ITALY', 'Italy', 'ITA', 380, 39),
('JM', 'JAMAICA', 'Jamaica', 'JAM', 388, 1876),
('JP', 'JAPAN', 'Japan', 'JPN', 392, 81),
('JO', 'JORDAN', 'Jordan', 'JOR', 400, 962),
('KZ', 'KAZAKHSTAN', 'Kazakhstan', 'KAZ', 398, 7),
('KE', 'KENYA', 'Kenya', 'KEN', 404, 254),
('KI', 'KIRIBATI', 'Kiribati', 'KIR', 296, 686),
('KP', 'KOREA, DEMOCRATIC PEOPLE''S REPUBLIC OF', 'Korea, Democratic People''s Republic of', 'PRK', 408, 850),
('KR', 'KOREA, REPUBLIC OF', 'Korea, Republic of', 'KOR', 410, 82),
('KW', 'KUWAIT', 'Kuwait', 'KWT', 414, 965),
('KG', 'KYRGYZSTAN', 'Kyrgyzstan', 'KGZ', 417, 996),
('LA', 'LAO PEOPLE''S DEMOCRATIC REPUBLIC', 'Lao People''s Democratic Republic', 'LAO', 418, 856),
('LV', 'LATVIA', 'Latvia', 'LVA', 428, 371),
('LB', 'LEBANON', 'Lebanon', 'LBN', 422, 961),
('LS', 'LESOTHO', 'Lesotho', 'LSO', 426, 266),
('LR', 'LIBERIA', 'Liberia', 'LBR', 430, 231),
('LY', 'LIBYAN ARAB JAMAHIRIYA', 'Libyan Arab Jamahiriya', 'LBY', 434, 218),
('LI', 'LIECHTENSTEIN', 'Liechtenstein', 'LIE', 438, 423),
('LT', 'LITHUANIA', 'Lithuania', 'LTU', 440, 370),
('LU', 'LUXEMBOURG', 'Luxembourg', 'LUX', 442, 352),
('MO', 'MACAO', 'Macao', 'MAC', 446, 853),
('MK', 'MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF', 'Macedonia, the Former Yugoslav Republic of', 'MKD', 807, 389),
('MG', 'MADAGASCAR', 'Madagascar', 'MDG', 450, 261),
('MW', 'MALAWI', 'Malawi', 'MWI', 454, 265),
('MY', 'MALAYSIA', 'Malaysia', 'MYS', 458, 60),
('MV', 'MALDIVES', 'Maldives', 'MDV', 462, 960),
('ML', 'MALI', 'Mali', 'MLI', 466, 223),
('MT', 'MALTA', 'Malta', 'MLT', 470, 356),
('MH', 'MARSHALL ISLANDS', 'Marshall Islands', 'MHL', 584, 692),
('MQ', 'MARTINIQUE', 'Martinique', 'MTQ', 474, 596),
('MR', 'MAURITANIA', 'Mauritania', 'MRT', 478, 222),
('MU', 'MAURITIUS', 'Mauritius', 'MUS', 480, 230),
('YT', 'MAYOTTE', 'Mayotte', NULL, NULL, 269),
('MX', 'MEXICO', 'Mexico', 'MEX', 484, 52),
('FM', 'MICRONESIA, FEDERATED STATES OF', 'Micronesia, Federated States of', 'FSM', 583, 691),
('MD', 'MOLDOVA, REPUBLIC OF', 'Moldova, Republic of', 'MDA', 498, 373),
('MC', 'MONACO', 'Monaco', 'MCO', 492, 377),
('MN', 'MONGOLIA', 'Mongolia', 'MNG', 496, 976),
('MS', 'MONTSERRAT', 'Montserrat', 'MSR', 500, 1664),
('MA', 'MOROCCO', 'Morocco', 'MAR', 504, 212),
('MZ', 'MOZAMBIQUE', 'Mozambique', 'MOZ', 508, 258),
('MM', 'MYANMAR', 'Myanmar', 'MMR', 104, 95),
('NA', 'NAMIBIA', 'Namibia', 'NAM', 516, 264),
('NR', 'NAURU', 'Nauru', 'NRU', 520, 674),
('NP', 'NEPAL', 'Nepal', 'NPL', 524, 977),
('NL', 'NETHERLANDS', 'Netherlands', 'NLD', 528, 31),
('AN', 'NETHERLANDS ANTILLES', 'Netherlands Antilles', 'ANT', 530, 599),
('NC', 'NEW CALEDONIA', 'New Caledonia', 'NCL', 540, 687),
('NZ', 'NEW ZEALAND', 'New Zealand', 'NZL', 554, 64),
('NI', 'NICARAGUA', 'Nicaragua', 'NIC', 558, 505),
('NE', 'NIGER', 'Niger', 'NER', 562, 227),
('NG', 'NIGERIA', 'Nigeria', 'NGA', 566, 234),
('NU', 'NIUE', 'Niue', 'NIU', 570, 683),
('NF', 'NORFOLK ISLAND', 'Norfolk Island', 'NFK', 574, 672),
('MP', 'NORTHERN MARIANA ISLANDS', 'Northern Mariana Islands', 'MNP', 580, 1670),
('NO', 'NORWAY', 'Norway', 'NOR', 578, 47),
('OM', 'OMAN', 'Oman', 'OMN', 512, 968),
('PK', 'PAKISTAN', 'Pakistan', 'PAK', 586, 92),
('PW', 'PALAU', 'Palau', 'PLW', 585, 680),
('PS', 'PALESTINIAN TERRITORY, OCCUPIED', 'Palestinian Territory, Occupied', NULL, NULL, 970),
('PA', 'PANAMA', 'Panama', 'PAN', 591, 507),
('PG', 'PAPUA NEW GUINEA', 'Papua New Guinea', 'PNG', 598, 675),
('PY', 'PARAGUAY', 'Paraguay', 'PRY', 600, 595),
('PE', 'PERU', 'Peru', 'PER', 604, 51),
('PH', 'PHILIPPINES', 'Philippines', 'PHL', 608, 63),
('PN', 'PITCAIRN', 'Pitcairn', 'PCN', 612, 0),
('PL', 'POLAND', 'Poland', 'POL', 616, 48),
('PT', 'PORTUGAL', 'Portugal', 'PRT', 620, 351),
('PR', 'PUERTO RICO', 'Puerto Rico', 'PRI', 630, 1787),
('QA', 'QATAR', 'Qatar', 'QAT', 634, 974),
('RE', 'REUNION', 'Reunion', 'REU', 638, 262),
('RO', 'ROMANIA', 'Romania', 'ROM', 642, 40),
('RU', 'RUSSIAN FEDERATION', 'Russian Federation', 'RUS', 643, 70),
('RW', 'RWANDA', 'Rwanda', 'RWA', 646, 250),
('SH', 'SAINT HELENA', 'Saint Helena', 'SHN', 654, 290),
('KN', 'SAINT KITTS AND NEVIS', 'Saint Kitts and Nevis', 'KNA', 659, 1869),
('LC', 'SAINT LUCIA', 'Saint Lucia', 'LCA', 662, 1758),
('PM', 'SAINT PIERRE AND MIQUELON', 'Saint Pierre and Miquelon', 'SPM', 666, 508),
('VC', 'SAINT VINCENT AND THE GRENADINES', 'Saint Vincent and the Grenadines', 'VCT', 670, 1784),
('WS', 'SAMOA', 'Samoa', 'WSM', 882, 684),
('SM', 'SAN MARINO', 'San Marino', 'SMR', 674, 378),
('ST', 'SAO TOME AND PRINCIPE', 'Sao Tome and Principe', 'STP', 678, 239),
('SA', 'SAUDI ARABIA', 'Saudi Arabia', 'SAU', 682, 966),
('SN', 'SENEGAL', 'Senegal', 'SEN', 686, 221),
('CS', 'SERBIA AND MONTENEGRO', 'Serbia and Montenegro', NULL, NULL, 381),
('SC', 'SEYCHELLES', 'Seychelles', 'SYC', 690, 248),
('SL', 'SIERRA LEONE', 'Sierra Leone', 'SLE', 694, 232),
('SG', 'SINGAPORE', 'Singapore', 'SGP', 702, 65),
('SK', 'SLOVAKIA', 'Slovakia', 'SVK', 703, 421),
('SI', 'SLOVENIA', 'Slovenia', 'SVN', 705, 386),
('SB', 'SOLOMON ISLANDS', 'Solomon Islands', 'SLB', 90, 677),
('SO', 'SOMALIA', 'Somalia', 'SOM', 706, 252),
('ZA', 'SOUTH AFRICA', 'South Africa', 'ZAF', 710, 27),
('GS', 'SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS', 'South Georgia and the South Sandwich Islands', NULL, NULL, 0),
('ES', 'SPAIN', 'Spain', 'ESP', 724, 34),
('LK', 'SRI LANKA', 'Sri Lanka', 'LKA', 144, 94),
('SD', 'SUDAN', 'Sudan', 'SDN', 736, 249),
('SR', 'SURINAME', 'Suriname', 'SUR', 740, 597),
('SJ', 'SVALBARD AND JAN MAYEN', 'Svalbard and Jan Mayen', 'SJM', 744, 47),
('SZ', 'SWAZILAND', 'Swaziland', 'SWZ', 748, 268),
('SE', 'SWEDEN', 'Sweden', 'SWE', 752, 46),
('CH', 'SWITZERLAND', 'Switzerland', 'CHE', 756, 41),
('SY', 'SYRIAN ARAB REPUBLIC', 'Syrian Arab Republic', 'SYR', 760, 963),
('TW', 'TAIWAN, PROVINCE OF CHINA', 'Taiwan, Province of China', 'TWN', 158, 886),
('TJ', 'TAJIKISTAN', 'Tajikistan', 'TJK', 762, 992),
('TZ', 'TANZANIA, UNITED REPUBLIC OF', 'Tanzania, United Republic of', 'TZA', 834, 255),
('TH', 'THAILAND', 'Thailand', 'THA', 764, 66),
('TL', 'TIMOR-LESTE', 'Timor-Leste', NULL, NULL, 670),
('TG', 'TOGO', 'Togo', 'TGO', 768, 228),
('TK', 'TOKELAU', 'Tokelau', 'TKL', 772, 690),
('TO', 'TONGA', 'Tonga', 'TON', 776, 676),
('TT', 'TRINIDAD AND TOBAGO', 'Trinidad and Tobago', 'TTO', 780, 1868),
('TN', 'TUNISIA', 'Tunisia', 'TUN', 788, 216),
('TR', 'TURKEY', 'Turkey', 'TUR', 792, 90),
('TM', 'TURKMENISTAN', 'Turkmenistan', 'TKM', 795, 7370),
('TC', 'TURKS AND CAICOS ISLANDS', 'Turks and Caicos Islands', 'TCA', 796, 1649),
('TV', 'TUVALU', 'Tuvalu', 'TUV', 798, 688),
('UG', 'UGANDA', 'Uganda', 'UGA', 800, 256),
('UA', 'UKRAINE', 'Ukraine', 'UKR', 804, 380),
('AE', 'UNITED ARAB EMIRATES', 'United Arab Emirates', 'ARE', 784, 971),
('GB', 'UNITED KINGDOM', 'United Kingdom', 'GBR', 826, 44),
('US', 'UNITED STATES', 'United States', 'USA', 840, 1),
('UM', 'UNITED STATES MINOR OUTLYING ISLANDS', 'United States Minor Outlying Islands', NULL, NULL, 1),
('UY', 'URUGUAY', 'Uruguay', 'URY', 858, 598),
('UZ', 'UZBEKISTAN', 'Uzbekistan', 'UZB', 860, 998),
('VU', 'VANUATU', 'Vanuatu', 'VUT', 548, 678),
('VE', 'VENEZUELA', 'Venezuela', 'VEN', 862, 58),
('VN', 'VIET NAM', 'Viet Nam', 'VNM', 704, 84),
('VG', 'VIRGIN ISLANDS, BRITISH', 'Virgin Islands, British', 'VGB', 92, 1284),
('VI', 'VIRGIN ISLANDS, U.S.', 'Virgin Islands, U.s.', 'VIR', 850, 1340),
('WF', 'WALLIS AND FUTUNA', 'Wallis and Futuna', 'WLF', 876, 681),
('EH', 'WESTERN SAHARA', 'Western Sahara', 'ESH', 732, 212),
('YE', 'YEMEN', 'Yemen', 'YEM', 887, 967),
('ZM', 'ZAMBIA', 'Zambia', 'ZMB', 894, 260),
('ZW', 'ZIMBABWE', 'Zimbabwe', 'ZWE', 716, 263),
('RS', 'SERBIA', 'Serbia', 'SRB', 688, 381),
('AP', 'ASIA PACIFIC REGION', 'Asia / Pacific Region', '0', 0, 0),
('ME', 'MONTENEGRO', 'Montenegro', 'MNE', 499, 382),
('AX', 'ALAND ISLANDS', 'Aland Islands', 'ALA', 248, 358),
('BQ', 'BONAIRE, SINT EUSTATIUS AND SABA', 'Bonaire, Sint Eustatius and Saba', 'BES', 535, 599),
('CW', 'CURACAO', 'Curacao', 'CUW', 531, 599),
('GG', 'GUERNSEY', 'Guernsey', 'GGY', 831, 44),
('IM', 'ISLE OF MAN', 'Isle of Man', 'IMN', 833, 44),
('JE', 'JERSEY', 'Jersey', 'JEY', 832, 44),
('XK', 'KOSOVO', 'Kosovo', 'XKX', 0, 383),
('BL', 'SAINT BARTHELEMY', 'Saint Barthelemy', 'BLM', 652, 590),
('MF', 'SAINT MARTIN', 'Saint Martin', 'MAF', 663, 590),
('SX', 'SINT MAARTEN', 'Sint Maarten', 'SXM', 534, 1),
('SS', 'SOUTH SUDAN', 'South Sudan', 'SSD', 728, 211);

-- inserting currencies 
INSERT INTO CURRENCY (name, code, symbol) VALUES
('Leke', 'ALL', 'Lek'),
('Dollars', 'USD', '$'),
('Afghanistan', 'AFN', '؋'),
('Pesos', 'ARS', '$'),
('Guilders', 'AWG', 'ƒ'),
('Dollars', 'AUD', '$'),
('New Manats', 'AZN', 'ман'),
('Dollars', 'BSD', '$'),
('Dollars', 'BBD', '$'),
('Rubles', 'BYR', 'p.'),
('Euro', 'EUR', '€'),
('Dollars', 'BZD', 'BZ$'),
('Dollars', 'BMD', '$'),
('Bolivianos', 'BOB', '$b'),
('Convertible Marka', 'BAM', 'KM'),
('Pula', 'BWP', 'P'),
('Leva', 'BGN', 'лв'),
('Reais', 'BRL', 'R$'),
('Pounds', 'GBP', '£'),
('Dollars', 'BND', '$'),
('Riels', 'KHR', '៛'),
('Dollars', 'CAD', '$'),
('Dollars', 'KYD', '$'),
('Pesos', 'CLP', '$'),
('Yuan Renminbi', 'CNY', '¥'),
('Pesos', 'COP', '$'),
('Colón', 'CRC', '₡'),
('Kuna', 'HRK', 'kn'),
('Pesos', 'CUP', '₱'),
('Koruny', 'CZK', 'Kč'),
('Kroner', 'DKK', 'kr'),
('Dollars', 'XCD', '$'),
('Pounds', 'EGP', '£'),
('Colones', 'SVC', '$'),
('Pounds', 'FKP', '£'),
('Dollars', 'FJD', '$'),
('Cedis', 'GHC', '¢'),
('Pounds', 'GIP', '£'),
('Quetzales', 'GTQ', 'Q'),
('Pounds', 'GGP', '£'),
('Dollars', 'GYD', '$'),
('Lempiras', 'HNL', 'L'),
('Dollars', 'HKD', '$'),
('Forint', 'HUF', 'Ft'),
('Kronur', 'ISK', 'kr'),
('Rupees', 'INR', '₹'),
('Rupiahs', 'IDR', 'Rp'),
('Rials', 'IRR', '﷼'),
('Pounds', 'IMP', '£'),
('New Shekels', 'ILS', '₪'),
('Dollars', 'JMD', 'J$'),
('Yen', 'JPY', '¥'),
('Pounds', 'JEP', '£'),
('Tenge', 'KZT', 'лв'),
('Won', 'KPW', '₩'),
('Won', 'KRW', '₩'),
('Soms', 'KGS', 'лв'),
('Kips', 'LAK', '₭'),
('Lati', 'LVL', 'Ls'),
('Pounds', 'LBP', '£'),
('Dollars', 'LRD', '$'),
('Switzerland Francs', 'CHF', 'CHF'),
('Litai', 'LTL', 'Lt'),
('Denars', 'MKD', 'ден'),
('Ringgits', 'MYR', 'RM'),
('Rupees', 'MUR', '₨'),
('Pesos', 'MXN', '$'),
('Tugriks', 'MNT', '₮'),
('Meticais', 'MZN', 'MT'),
('Dollars', 'NAD', '$'),
('Rupees', 'NPR', '₨'),
('Guilders', 'ANG', 'ƒ'),
('Dollars', 'NZD', '$'),
('Cordobas', 'NIO', 'C$'),
('Nairas', 'NGN', '₦'),
('Krone', 'NOK', 'kr'),
('Rials', 'OMR', '﷼'),
('Rupees', 'PKR', '₨'),
('Balboa', 'PAB', 'B/.'),
('Guarani', 'PYG', 'Gs'),
('Nuevos Soles', 'PEN', 'S/.'),
('Pesos', 'PHP', 'Php'),
('Zlotych', 'PLN', 'zł'),
('Rials', 'QAR', '﷼'),
('New Lei', 'RON', 'lei'),
('Rubles', 'RUB', 'руб'),
('Pounds', 'SHP', '£'),
('Riyals', 'SAR', '﷼'),
('Dinars', 'RSD', 'Дин.'),
('Rupees', 'SCR', '₨'),
('Dollars', 'SGD', '$'),
('Dollars', 'SBD', '$'),
('Shillings', 'SOS', 'S'),
('Rand', 'ZAR', 'R'),
('Rupees', 'LKR', '₨'),
('Kronor', 'SEK', 'kr'),
('Dollars', 'SRD', '$'),
('Pounds', 'SYP', '£'),
('New Dollars', 'TWD', 'NT$'),
('Baht', 'THB', '฿'),
('Dollars', 'TTD', 'TT$'),
('Lira', 'TRY', '₺'),
('Liras', 'TRL', '£'),
('Dollars', 'TVD', '$'),
('Hryvnia', 'UAH', '₴'),
('Pesos', 'UYU', '$U'),
('Sums', 'UZS', 'лв'),
('Bolivares Fuertes', 'VEF', 'Bs'),
('Dong', 'VND', '₫'),
('Rials', 'YER', '﷼'),
('Zimbabwe Dollars', 'ZWD', 'Z$'),
('Algerian dinar', 'DZD', 'DA'),
('Angolan kwanza', 'AOA', 'Kz'),
('Armenian dram', 'AMD', '֏'),
('Bahraini dinar', 'BHD', 'BD'),
('Bangladeshi taka', 'BDT', '৳'),
('West African CFA franc', 'XOF', 'CFA'),
('Burundian franc', 'BIF', 'FBu'),
('Central African CFA franc', 'XAF', 'FCFA'),
('Cape Verdean escudo', 'CVE', 'Esc'),
('Comorian franc', 'KMF', 'CF'),
('Djiboutian franc', 'DJF', 'Fdj'),
('Dominican peso', 'DOP', 'RD$'),
('Eritrean nakfa', 'ERN', 'Nkf'),
('Ethiopian birr', 'ETB', 'Br'),
('CFP franc', 'XPF', '₣'),
('Gambian dalasi', 'GMD', 'D'),
('Georgian lari', 'GEL', 'ლ'),
('Ghanaian cedi', 'GHS', 'GH₵'),
('Guinean franc', 'GNF', 'FG'),
('Iraqi dinar', 'IQD', 'ع.د'),
('Jordanian dinar', 'JOD', 'د.ا'),
('Kenyan shilling', 'KES', 'Ksh'),
('Kuwaiti dinar', 'KWD', 'د.ك'),
('Libyan dinar', 'LYD', 'ل.د'),
('Macanese pataca', 'MOP', 'MOP$'),
('Malagasy ariary', 'MGA', 'Ar'),
('Malawian kwacha', 'MWK', 'MK'),
('Maldivian rufiyaa', 'MVR', 'Rf'),
('Mauritanian ouguiya', 'MRO', 'UM'),
('Moldovan leu', 'MDL', 'L'),
('Moroccan dirham', 'MAD', 'MAD'),
('Myanmar kyat', 'MMK', 'K'),
('Papua New Guinean kina', 'PGK', 'K'),
('Rwandan franc', 'RWF', 'R₣'),
('Samoan tālā', 'WST', 'WS$'),
('São Tomé and Príncipe dobra', 'STD', 'Db'),
('Sierra Leonean leone', 'SLL', 'Le'),
('South Sudanese pound', 'SSP', '£'),
('Sudanese pound', 'SDG', 'ج.س'),
('Swazi lilangeni', 'SZL', 'L'),
('Tajikistani somoni', 'TJS', 'ЅM'),
('Tanzanian shilling', 'TZS', 'TSh'),
('Tongan paʻanga', 'TOP', 'T$'),
('Tunisian dinar', 'TND', 'DT'),
('Turkmenistani manat', 'TMT', 'T'),
('Ugandan shilling', 'UGX', 'USh'),
('United Arab Emirates dirham', 'AED', 'د.إ'),
('Vanuatu vatu', 'VUV', 'VT'),
('Zambian kwacha', 'ZMW', 'ZK'),
('Zimbabwean dollar', 'ZWL', '$'),
('Pakistani Rupees', 'PKR', '/=');


