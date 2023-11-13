# OS Group Assignment - 2

## Team Members:

#### Add your names here:

1. Malladi Pradyumna

## Setup Instructions:

```
find . -name "secondary_server.c" | entr -r sh -c 'echo "" && echo "Change Detected! Building...." && echo "" && echo "" && gcc secondary_server.c -o secondary_server.bin && ./secondary_server.bin 1 & ./secondary_server.bin 2'
```
