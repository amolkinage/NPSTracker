#include <math.h>
#include "xirrtransaction.h"

// Calculates the resulting amount
double irrResult(xirrTransactions transactions,double rate)
{
    double  r = rate + 1;
    double  result =  transactions[0].amount;

    QDate date0 = transactions[0].date;

    for (int  i = 1; i < transactions.count(); i++) {
        double amount = transactions[i].amount;
        QDate datei = transactions[i].date;
        double days = datei.daysTo(date0);
        result += amount / pow(r, days/365);
    }
    return result;
}

// Calculates the first derivation
double irrResultDeriv(xirrTransactions transactions,double rate)
{
    double r = rate + 1;
    double  result = 0;
    QDate date0 = transactions[0].date;

    for (int  i = 1; i < transactions.count(); i++) {
      double amount = transactions[i].amount;
      QDate datei = transactions[i].date;
      double days = datei.daysTo(date0);
      double frac =  days / 365;
      result -= frac * amount / pow(r, frac + 1);
    }
    return result;
}

double CalculateXIRR(xirrTransactions transactions,double rate)
{
  // Credits: algorithm inspired by Apache OpenOffice

  // Check that values contains at least one positive value and one negative value
  bool positive = false;
  bool negative = false;
  for (int i = 0; i < transactions.count(); i++) {
    if (transactions[i].amount > 0) positive = true;
    if (transactions[i].amount < 0) negative = true;
  }

  // Return error if values does not contain at least one positive value and one negative value
  if (!positive || !negative) return NAN;

  // Initialize guess and resultRate
  double guess =  rate;
  double resultRate = guess;

  // Set maximum epsilon for end of iteration
  double epsMax = 1e-10;

  // Set maximum number of iterations
  int iterMax = 500;

  // Implement Newton's method
  double newRate, epsRate, resultValue;
  int iteration = 0;
  int contLoop = true;

  do {
    resultValue = irrResult(transactions, resultRate);
    newRate = resultRate - resultValue / irrResultDeriv(transactions, resultRate);
    epsRate = fabs(newRate - resultRate);
    resultRate = newRate;
    contLoop = (epsRate > epsMax) && (fabs(resultValue) > epsMax);
  } while(contLoop && (++iteration < iterMax));

  if(contLoop) return NAN;

  // Return internal rate of return
  return resultRate;
}

