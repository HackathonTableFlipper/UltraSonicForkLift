| Device |      |      |
| ------ | ---- | ---- |
| <u>macaddress</u> | Varchar(48) | Unique |
| name | Varchar(32) | Unique (Location) |
| location | Varchar(32) |    |



| Log |      |      |
| ------ | ---- | ---- |
| <u>macaddress</u> | Varchar(48) | Unique (FOREIGN KEY) |
| load | Tinyint (1) | NOT NULL |
| start | DateTime | NOT NULL |
| end | DateTime | NOT NULL |

