#include "signup.h"


Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);

//    data::Location l;
//    std::vector<data::Location> vl;
//    QStringList wlcountry;
//    QStringList wlcity;
//    QStringList wladdress;
//    std::string select, from, where;
//    select = "*"; from = "locations"; where = "";
//    db::PSQL::getInstance()->get(&select, &from, &where, &vl);
//    for (auto i : vl) {
//        wlcountry.append(i.getCountry().c_str());
//        wlcity.append(i.getCity().c_str());
//        wladdress.append(i.getAddress().c_str());
//    }
//    QCompleter* countryCompleter = new QCompleter(wlcountry,this);
//    countryCompleter->setCaseSensitivity(Qt::CaseInsensitive);
//    ui->le_country->setCompleter(countryCompleter);
//    QCompleter* cityCompeter = new QCompleter(wlcity,this);
//    cityCompeter->setCaseSensitivity(Qt::CaseSensitive);
//    ui->le_city->setCompleter(cityCompeter);
//    QCompleter* addrCompleter = new QCompleter(wladdress,this);
//    addrCompleter->setCaseSensitivity(Qt::CaseInsensitive);
//    ui->le_address->setCompleter(addrCompleter);

}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_btn_signup_clicked()
{
    std::string name, email, cnic, contact, country, city, address, password, confPass;
     name = ui->le_name->text().toStdString();
     email = ui->le_email->text().toStdString();
     cnic = ui->le_cnic->text().toStdString();
     contact = ui->le_contact->text().toStdString();
     country = ui->le_country->text().toLower().toStdString();
     city = ui->le_city->text().toLower().toStdString();
     address = ui->le_address->text().toLower().toStdString();
     password = ui->le_password->text().toStdString();
     confPass = ui->le_conf_password->text().toStdString();

    if (name.empty()) { QMessageBox::critical(this,"error","Please enter name"); return;}
    if (email.empty()) { QMessageBox::critical(this,"error","Please enter email");  return;}
    if (cnic.empty()) { QMessageBox::critical(this,"error","Please enter cnic");   return;}
    if (cnic.length() != 13) { QMessageBox::critical(this,"error","Please user 13 digits for cnic");   return;}
    if (contact.empty()) { QMessageBox::critical(this,"error","Please enter contact");  return;}
    if (country.empty()) { QMessageBox::critical(this,"error","Please enter country");  return;}
    if (city.empty()) { QMessageBox::critical(this,"error","Please enter city");  return;}
    if (address.empty()) { QMessageBox::critical(this,"error","Please enter address");  return;}
    if (password.empty()) { QMessageBox::critical(this,"error","Please enter password");  return;}
    if (confPass.empty()) { QMessageBox::critical(this,"error","Please enter confirm password"); return; }
    if (password != confPass) { QMessageBox::critical(this,"error","Password Missmatch");  return;}
    if (password.length() <8 ) { QMessageBox::critical(this,"error","please use more than 8 characters for password"); return;}

    std::vector<data::Email> e;
    std::vector<data::Contact> c;
    std::vector<data::CNIC> cid;
    std::vector<data::Location> lv;
    std::vector<data::Person> p;
    std::string pass;
    std::string q = "insert into emails(email) values ('" + email +"')";
    db::PSQL::getInstance()->set(&q);
    q = " insert into cnics(cnic) values ('"+ cnic +"')";
    db::PSQL::getInstance()->set(&q);
    q = "insert into contacts (contact) values ('" + contact + "')";
    db::PSQL::getInstance()->set(&q);

    std::string select, from, where;
    select = "*";
    from = "locations";
    where = "city ='"+city+"' and country ='"+country+"' and address = '"+address+"'";

    db::PSQL::getInstance()->get(&select, &from, &where ,&lv);
    if (lv.size() < 1) {
        q = "insert into locations(city, country, address) values ('" + city + "','" + country + "','" + address +"')";

//        q = "insert into locations (city, country, address) select '" + city + "'" + country + "'" + address + "' where not exists ( select city,country,address from locations where city ='"+ city + "' and country = '" + country + "' and address = '" + address + "' )";

        db::PSQL::getInstance()->set(&q);
    }
    db::PSQL::getInstance()->get(&select, &from, &where ,&lv);

    from = "emails";
    where = "email ='" + email + "'";
    db::PSQL::getInstance()->get(&select, &from, &where, &e);

    from = "cnics";
    where = "cnic ='" + cnic + "'";
    db::PSQL::getInstance()->get(&select, &from, &where, &cid);

    from = "contacts";
    where = "contact ='" + contact + "'";
    db::PSQL::getInstance()->get(&select, &from, &where, &c);

    q = "insert into persons(name,emailid,contactid,cnicid,locationid) values ('"+name+"','"+e.at(0).getId()+"','"+c.at(0).getId()+"','"+cid.at(0).getId()+"','"+lv.at(0).getId()+"')";
    db::PSQL::getInstance()->set(&q);
    q = "insert into auth(password, emailid) values ('" + password + "','" + e.at(0).getId() + "')";
    db::PSQL::getInstance()->set(&q);

    from = "persons";
    where = "emailid ='" + e.at(0).getId() + "'";
    db::PSQL::getInstance()->get(&select, &from, &where, &p);

    q = "insert into users(personid)values('"+p.at(0).getId()+"')";
    db::PSQL::getInstance()->set(&q);

//    data::Auth a = data::Auth(&email,&password);

}

