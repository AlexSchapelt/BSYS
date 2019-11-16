#!/bin/bash
pages=1
while [ "$pages" -lt "5000" ]; do
	./tlb "$pages" "100" >> data.csv
	let "pages+=2"
done
