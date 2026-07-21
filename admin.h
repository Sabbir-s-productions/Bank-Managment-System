#ifndef ADMIN_H
#define ADMIN_H

void createDefaultPassword();
void login();
void changeAdminPassword();

void dashboard();

// report.h
void bankStatistics();
void top5Customers();

void exportCSV();

void backupDatabase();
void restoreDatabase();

#endif