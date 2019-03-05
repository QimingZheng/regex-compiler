:<<H
id=0
for line in $(cat $1)
do
	let "id = id + 1"
	#echo ${line}
	./tool "${line}" snort-3.0/$id.nfa
done
H

id=0
for i in *.nfa
do
	python eliminate_nop.py $i > ../snort/$i
done
