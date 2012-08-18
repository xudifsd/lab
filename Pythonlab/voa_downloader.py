from HTMLParser import HTMLParser
from htmlentitydefs import name2codepoint
from Queue import Queue
from threading import Thread
import urllib2
import re

#This program is used to download a page of the mp3 file and subscribe from http://www.hxen.com

debug = 0

class Parser(HTMLParser):
	escapeChar = {'62':'>', 'gt':'>', '60':'<', 'lt':'<', '160':' ', 'nbsp':' ', '38':'&','amp':'&',\
		'34':'"', 'quot':'"', '215':'*', 'times':'*', '247':'/', 'divide':'/', '8216':'\'', 'lsquo':'\'',\
			'8217':'\'', 'rsquo':'\'', '8220':'"', 'ldquo':'"', '8221':'"', 'rdquo':'"'}
	linkReg = re.compile(r'<a href="(.*?)".*?>')
	titleReg = re.compile(r'<title.*?>')
	def __init__(self):
		HTMLParser.__init__(self)

		self.title = ''
		self.content = ''
		self.links = {}
		self.in_content = False
	def handle_charref(self, name):
		tag = self.get_starttag_text()
		title = Parser.titleReg.findall(tag)

		if self.in_content:
			if Parser.escapeChar.has_key(name):
				self.content += Parser.escapeChar[name]
		elif len(title):
			if Parser.escapeChar.has_key(name):
				self.title += Parser.escapeChar[name]
	def handle_entityref(self, name):
		tag = self.get_starttag_text()
		title = Parser.titleReg.findall(tag)

		if self.in_content:
			if Parser.escapeChar.has_key(name):
				self.content += Parser.escapeChar[name]
		elif len(title):
			if Parser.escapeChar.has_key(name):
				self.title += Parser.escapeChar[name]
	def handle_starttag(self, tag, attrs):
		if tag == 'p':
			self.in_content = True
		if tag == 'div':
			self.in_content = False
	def handle_endtag(self, tag):
		if tag == 'p':
			self.in_content = False
	def handle_startendtag(self, tag, attrs):
		if tag == 'br':
			if self.in_content and self.content[-1] == '\n':
				self.content += '\n'
	def handle_data(self, data):
		tag = self.get_starttag_text()
		if tag:
			links = Parser.linkReg.findall(tag)
			title = Parser.titleReg.findall(tag)

			if self.in_content:
				self.content += data

			if len(links) and not self.links.has_key(links[0]):
				self.links[data] = links[0]
			elif len(title):
				self.title += data

def save(content, name):
	f = open(name, 'w')
	try:
		f.write(content)
	except UnicodeEncodeError:
		print "error content is '''%s'''"%content
	finally:
		f.close()

def extract_title(page):
	titleRegex = re.compile(r'.*:([^|]*)[|].*')
	title = titleRegex.findall(page)[0]
	return title

def fetch_url(url):
	print('fetching ' + url)
	try:
		page = urllib2.urlopen(url).read()
	except urllib2.HTTPError:
		print '%s cannot open'%url
	except urllib2.URLError:
		print '%s url error'%url
	return page

class PageFetcher(Thread):
	mp3Regex = re.compile(r'.*?.mp3')
	def __init__(self, queue):
		Thread.__init__(self)
		self.queue = queue
	def run(self):
		while not self.queue.empty():
			url = self.queue.get()
			page = fetch_url(url)
			parser = Parser()
			try:
				parser.feed(page.decode('gbk'))
			except:
				self.queue.task_done()
				print 'encount exception when fetching ' + url
				continue
			title = extract_title(parser.title).strip()

			for i in parser.links.values():
				rtn = PageFetcher.mp3Regex.findall(i)
				if len(rtn):
					mp3_url = i
			mp3Content = fetch_url(mp3_url)

			save(parser.content.strip(), title + '.txt')
			save(mp3Content, title + '.mp3')
			self.queue.task_done()

def fetch_index(index_url):
	pageReg = re.compile(r'VOA.*?:.*?')
	site = 'http://www.hxen.com' #for internal url
	index = fetch_url(index_url)
	parser = Parser()
	try:
		parser.feed(index.decode('gbk'))
	except:
		print 'encount exception when fetching ' + url
		return

	pagesText = parser.links.keys()
	queue = Queue()
	for i in pagesText:
		rtn = pageReg.findall(i)
		if len(rtn):
			queue.put(site + parser.links[i])
	for i in range(10):
		t = PageFetcher(queue)
		t.setDaemon(True)
		t.start()
	queue.join()
	print "finished downloading"

if __name__ == "__main__":
	fetch_index("http://www.hxen.com/englishlistening/voaenglish/voastandardenglish/")
