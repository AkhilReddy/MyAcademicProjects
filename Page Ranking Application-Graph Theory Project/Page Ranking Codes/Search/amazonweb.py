import requests
from bs4 import BeautifulSoup

def trade_spider(maxpages):
 page = 2
 while page <= maxpages:
     url = 'http://www.amazon.in/s/rh=n%3A976419031%2Cn%3A%21976420031%2Cn%3A1389401031%2Cp_36%3A-1500000%2Cn%3A1389432031%2Cn%3A1805560031&page='+str(page)
     data = requests.get(url)
     plaintext = data.text
     soup = BeautifulSoup(plaintext)
     for link in soup.findAll('a',{'class':'a-link-normal s-access-detail-page  a-text-normal'}): #this gone do loop through source code get the links of class
         href=link.get('href')
         print href
     page+=1

maxpages = 5;
trade_spider(maxpages)





