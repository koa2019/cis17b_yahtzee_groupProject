Netbeans > properties > run configuration > Project URL > http://localhost/folderName/ i.e. http://localhost/survey_phpJS_v4/

* This project folder HAS to be in XAMPP > htdocs for it to run with the XAMPP server.

1. Make sure XAMPP's Apache and MySQL are running. 

2. In MySQL workbench: 
   a. Click on localhost connect. If there isn't a connection 
      then see folder images to setup a new localhost connection.
   b. If entity_user_votes already exists in MySQL, then drop it.
   c. Click Open SQL script and select test_entity_user_votes.sql file 
      from this project folder.
   d. Click the lightning symbol to run and set this table in database.
  
3. Open OpenOffice app:
   a. Select database.
   b. Open existing database: Survey_DBConnect_2.obd file from within this project folder.
4. In Netbeans open this folder, select the page you want to run. i.e. DBSelectAll.php
   and right click run file on the file you want to execute. All the records stored
   in the test_entity_user_votes.sql file should be written to a localhost webrowser.

See folder with images. 1_survey_github > survey_code_html > html_docs> config_screenshots


