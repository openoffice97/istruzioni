import os, glob

path = 'D:\\formattazione\\Icing\\Freezing_Melting cycle'
tracker=''
folders = []


# r=root, d=directories, f = files
for r, d, f in os.walk(path):
    for folder in d:
        if '.' in folder.split('\\')[0]:
            folders.append(os.path.join(r, folder))

index=0
for f in folders:
    os.chdir(f)
    print(f)
    for file in glob.glob("*.txt"):
        if not 'comments' in file.lower():
            file2 = open(file, "r")
            all_text=file2.readlines()
            
            i=0
#            icristi=all_text[i].split('\t')
            for i in range(len(all_text)):
                icristi=all_text[i].split('\t')
                if len(all_text[i].split('\t'))>3:
                    if '1' in all_text[i].split('\t')[3]:
                        print(i)
                        break
            
            if i==len(all_text)-1:
                i=5
            file2.close()
            useful=''
            for k in range(i,len(all_text)):
                useful=useful+all_text[k]
            file2=open('D:\\Ulde\\Test#' + str(index) +'.txt','w+')
            file2.write(useful[:-2])
            file2.close()
            tracker=tracker + 'D:\\Ulde\\Test#' + str(index) +'.txt,'+str(f)+'\\'+file+'\n'
            file2=open('D:\\Ulde\\TrackerFile.txt','w+')
            file2.write(tracker)
            file2.close()
            index=index+1
