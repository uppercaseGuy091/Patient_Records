#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct birthday
{
    char date;
    char month;
    int year;
};

struct address
{
    char city[15];
    char streetName[25];
    int streetNumber;
    unsigned short postcode;
};

struct vaccinationHistory
{

    unsigned int yellowFever : 1;
    unsigned int hepatitis : 1;
    unsigned int malaria : 1;
    unsigned int birdFlue : 1;
    unsigned int polio : 1;
};

union additionalInfo
{
    float sodiumLevel;
    float potassiumLevel;
    char school[15];
};

struct healthRecord
{
    char firstName[10];
    char lastName[10];
    struct birthday dateOfBirth;
    char gender[1];
    int height;
    float weight;
    float bmi;
    struct address address;
    struct vaccinationHistory vaccHist;
    union additionalInfo additionalInfoStructure;
};

struct healthRecord hr[10];

void getPatientProfile(struct healthRecord *patientInfo);
void showPatientProfile(struct healthRecord *patientInfo, int i);
void savePatientProfile(struct healthRecord *patientData);
void readPatientProfile(struct healthRecord *patientData);
void sortPatients();


int main()
{

    printf("The size of the structure is %d.\n\n", sizeof(struct healthRecord));        //I counted 108 by hand
    getPatientProfile(hr);
    savePatientProfile(hr);

    readPatientProfile(hr);
    sortPatients();

    for(int i = 0; i<10; i++)
    {
        showPatientProfile(hr+i, i);
    }

    return 0;
}



float calculateBMI(int height, float weight)
{
    float bmi = (weight/ height/ height)*10000;
    return bmi;
}

void getPatientProfile(struct healthRecord *patientInfo)
{

    for(int i = 0; i<10; i++)
    {
        char y;

        printf("Enter patient first name: ");
        scanf("%s", patientInfo->firstName);

        printf("\nEnter patient last name: ");
        scanf("%s", patientInfo->lastName);
        printf("\nEnter patient date of birth (date month year): ");
        scanf("%d %d %d", &patientInfo->dateOfBirth.date, &patientInfo->dateOfBirth.month, &patientInfo->dateOfBirth.year);
        printf("\nEnter patient gender (M/F): ");
        scanf("%s", patientInfo->gender);
        printf("\nEnter patient height in cm: ");
        scanf("%d", &patientInfo->height);
        printf("\nEnter patient weight in kg: ");
        scanf("%f", &patientInfo->weight);
        patientInfo->bmi = calculateBMI(patientInfo->height, patientInfo->weight);


        printf("\nEnter patient address (Street name, street number, city, postcode): ");
        scanf("%s %d %s %d", patientInfo->address.streetName, &patientInfo->address.streetNumber, patientInfo->address.city, &patientInfo->address.postcode);

        printf("\nVaccination History:");
        printf("\nYellow Fever (Y/N): ");
        getchar();
        scanf("%c", &y);
        if(y=='y'||y=='Y')
        {
            patientInfo->vaccHist.yellowFever = 1;
        }
        printf("\nHepatitis (Y/N): ");
        getchar();
        scanf("%c", &y);
        if(y=='y'||y=='Y')
        {
            patientInfo->vaccHist.hepatitis = 1;
        }
        printf("\nMalaria (Y/N): ");
        getchar();
        scanf("%c", &y);
        if(y=='y'||y=='Y')
        {
            patientInfo->vaccHist.malaria = 1;
        }
        printf("\nBird Flue (Y/N): ");
        getchar();
        scanf("%c", &y);
        if(y=='y'||y=='Y')
        {
            patientInfo->vaccHist.birdFlue = 1;
        }
        printf("\nPolio (Y/N): ");
        getchar();
        scanf("%c", &y);
        if(y=='y'||y=='Y')
        {
            patientInfo->vaccHist.polio = 1;
        }


        if(2019 - patientInfo->dateOfBirth.year < 16)
        {
            printf("\nWhat type of school does the child attend: ");
            scanf("%s", patientInfo->additionalInfoStructure.school);
        }
        else if(*patientInfo->gender == 'm' || *patientInfo->gender == 'M')
        {
            printf("\nEnter sodium level (normal range 135-145): ");
            scanf("%f", &patientInfo->additionalInfoStructure.sodiumLevel);
        }
        else if(*patientInfo->gender == 'f' || *patientInfo->gender == 'F')
        {
            printf("\nEnter potassium level (normal range 2.5 - 3.5): ");
            scanf("%f", &patientInfo->additionalInfoStructure.potassiumLevel);
        }

        patientInfo++;
    }
}

void showPatientProfile(struct healthRecord *patientInfo, int i)
{
    getchar();
    printf("-----PATIENT %d PROFILE-----\n", i+1);
    printf("\nFirst name: %s", patientInfo->firstName);
    printf("\nLast name: %s", patientInfo->lastName);
    printf("\nDate of birth: %d/%d/%d", patientInfo->dateOfBirth.date, patientInfo->dateOfBirth.month, patientInfo->dateOfBirth.year);
    printf("\nGender: %s", patientInfo->gender);
    printf("\nHeight: %d", patientInfo->height);
    printf("\nWeight: %.1f", patientInfo->weight);
    printf("\nBMI: %.2f", patientInfo->bmi);
    printf("\nAddress: %s, %d, %s, %d",  patientInfo->address.streetName, patientInfo->address.streetNumber, patientInfo->address.city, patientInfo->address.postcode);
    printf("\nVaccination History:\n");

    if(patientInfo->vaccHist.yellowFever == 1)
    {
        printf("Yellow Fever");
    }
    if(patientInfo->vaccHist.hepatitis==1)
    {
        printf("\nHepatitis");
    }
    if(patientInfo->vaccHist.malaria==1)
    {
        printf("\nMalaria");
    }
    if(patientInfo->vaccHist.birdFlue==1)
    {
        printf("\nBird Flue");
    }
    if(patientInfo->vaccHist.polio == 1)
    {
        printf("\nPolio");
    }

    printf("\n");
    if(2019 - patientInfo->dateOfBirth.year < 16)
    {
        printf("\nSchool: %s", patientInfo->additionalInfoStructure.school);
    }
    else if(*patientInfo->gender == 'm' || *patientInfo->gender == 'M')
    {
        printf("\nSodium level: %.1f", patientInfo->additionalInfoStructure.sodiumLevel);
    }
    else if(*patientInfo->gender == 'f' || *patientInfo->gender == 'F')
    {
        printf("\nPotassium level: %.1f", patientInfo->additionalInfoStructure.potassiumLevel);
    }
    printf("\n\n");
}

void savePatientProfile(struct healthRecord *patientData)
{
    FILE *fp = fopen("Patients.txt", "wb");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fwrite(patientData, sizeof(struct healthRecord), 10, fp);
    printf("\nData is stored successfully to file!\n");

    fclose(fp);
}

void readPatientProfile(struct healthRecord *patientData)
{
    FILE *fp = fopen("Patients.txt", "rb");

    if (patientData == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("Reading from file:\n");
    fread(patientData, sizeof(struct healthRecord), 10, fp);

    fclose(fp);
}

void sortPatients ()
{
    struct healthRecord temp;
    int i, j;
    for (j = 0; j<10-1; j++)
    {
        for(i=0; i<10-j-1; i++)
        {
            if (hr[i].bmi > hr[i+1].bmi)
            {
                temp = hr[i];
                hr[i] = hr[i+1];
                hr[i+1] = temp;
            }
        }
    }
}
