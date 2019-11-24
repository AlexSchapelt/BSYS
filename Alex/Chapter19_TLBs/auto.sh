#!/bin/bash
rm ./data.csv
pages=1
while [ "$pages" -lt "5000" ]; do
	./tlb "$pages" "100" >> data.csv
	if [ "$pages" -lt "100" ]
	then 
		let "pages+=2"
	else
		let "pages+=100"
	fi
done
