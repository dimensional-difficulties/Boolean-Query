Boolean-Query
=============

Allows user to search text files for keywords using Boolean operators

Upon starting the program, files with names given in file_list.txt are immediately loaded.  You can add more files
by entering "ADD_FILE" followed by a space and then the file name.  

Enter the word "QUERY" followed by a space and then your query.  Queries can contain words or boolean operators.  
The boolean operators "|" for or and "&" for and may be used.  Also, parentheses may be used to change the order in
which boolean operators are handled.  

As an example, entering the query "(some & say) & (fire | ice)" would return all lines that contain both the words
"some" and "say" and either the words "fire" or "ice" or both.  
