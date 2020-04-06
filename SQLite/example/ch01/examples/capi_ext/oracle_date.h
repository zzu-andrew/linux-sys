typedef struct {
    int month;
    int day;
    int year;
} date;

int is_valid_oracle_date(const char* value);
const char* iso_from_oracle_date(const char* value);
int oracle_date_str_to_struct(const char* value, date* d);

