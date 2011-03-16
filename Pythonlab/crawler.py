import urllib2
import re
TitleRegex=re.compile(r'<title>(.*?)</title>')
LinkRegex=re.compile(r'<a href="(http://.*?)"')
def crawler(source,age=0):
   if age<=10:
        try:
#open url
            content=urllib2.urlopen(source).read()
        except urllib2.HTTPError:
            print '%s cannot open'%source
        except urllib2.URLError:
            print '%s url error'%source
        except:
            pass
        
        else:
            title=TitleRegex.findall(content)
#save page
            f=open(title[0]+'.html','w')
            f.write(content)
            f.close()
#crawler another page
            link=LinkRegex.findall(content)
            del content
            print age
            for i in link:
                crawler(i,age+1)
if __name__ == "__main__":
    a=raw_input('Enter websit:\n')
    crawler(a)