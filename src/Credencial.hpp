#ifndef CREDENCIAL_H
#define CREDENCIAL_H

#include <bits/stdc++.h>

using namespace std;

class Credencial {
    public:
        Credencial(string ssid, string password) : ssid_(ssid), password_(password) {}
        string ssid() const { return ssid_; }
        string password() const { return password_; }
    private:
        string ssid_;
        string password_;
};

#endif