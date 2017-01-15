#!/usr/bin/python
# -*- coding: utf-8 -*-
# Author: snuke

usage = '''
usage: python md2atcoder.py <markdown file> (<markdown file>)
markdown fileは日本語と英語で２つまで指定できます。
言語を自動判定して、atcoderの仕様に合わせてマージされたhtmlを吐きます。
問題・制約（・部分点）・入力・出力・入出力例の順で記述してください。
'''

import codecs
import os
import re
import sys

from markdown import markdown
from markdown.extensions import Extension
from markdown.preprocessors import Preprocessor

THRESHOLD_JA_EN = 30

# language detection
CURRENT_LANG = 'ja'
def detect_lang(s):
	global CURRENT_LANG
	if len(re.findall(u'[亜-熙ぁ-んァ-ヶ]', s)) >= THRESHOLD_JA_EN:
		CURRENT_LANG = 'ja'
	else:
		CURRENT_LANG = 'en'

# extensions
class MyExtension(Extension):

	def extendMarkdown(self, md, md_globals):
		# sample: {sample filename}
		# TIPS: complement ".txt" or ".in" or ".out" automatically
		class SamplePreprocessor(Preprocessor):

			def run(self, lines):
				new_lines = []
				samples = set()
				for line in lines:
					m = re.match(r'\{sample (.*)\}', line)
					if m:
						fname = m.group(1)
						assert fname not in samples, 'duplicated sample'
						samples.add(fname)
						sample_id = len(samples)
						dt = [['in', u'入力例'], ['out', u'出力例']]
						if CURRENT_LANG == 'en':
							dt = [['in', u'Sample Input'], ['out', u'Sample Output']]
						for d, t in dt:
							new_lines.append(u'{} {}'.format(t, sample_id))
							new_lines.append('-' * 8)
							new_lines.append('~' * 3)
							
							extensions = ['','.txt','.' + d]
							error_message = ''
							for extension in extensions:
								try:
									with open(os.path.join('..', d, fname + extension)) as f:
										s = f.read()
										s = re.sub('(\r\n|\r)', '\n', s)
										break
								except Exception as e:
									error_message += str(e) + '\n'
							else:
								s = error_message
							
							new_lines += s.split('\n')[:-1]
							new_lines.append('~' * 3)
							new_lines.append('')
					else:
						new_lines.append(line)
				return new_lines

		# centered figure: !![caption](url)
		class FigurePreprocessor(Preprocessor):

			def run(self, lines):
				new_lines = []
				for line in lines:
					m = re.match(r'!!\[(.*)\]\((.*)\)', line)
					if m:
						caption, url = m.group(1, 2)
						new_lines.append('<div style="text-align: center;">')
						if caption == '':
							alt = os.path.basename(url)
							new_lines.append(
								u'<img alt="{}" src="{}" />'.format(alt, url))
						else:
							new_lines.append(u'<img src="{}" />'.format(url))
							new_lines.append(u'<p>{}</p>'.format(caption))
						new_lines.append('</div>')
					else:
						new_lines.append(line)
				return new_lines
		
		# sample: {score} => (MaxPoint) or {score subtask1 subtask2} => (sum of subtask1 and subtask2's points)
		# TODO: 実は{scoreAll}みたいなのでも動いちゃうので修正すること。これは後で{scorepiyo}みたいな拡張を作る時に困るかも。場合分けすると記述量が増えるから嫌だった。
		class ScorePreprocessor(Preprocessor):
			def run(self, lines):
				new_lines = []
				for line in lines:
					while True:
						m = re.search(r'\{score\s?(.*?)\}', line)
						if not m:
							break
						tasknames = [x for x in m.group(1).split(' ') if x != ""] # 空文字列除去 ["All","","Sub1"] -> ["All","Sub1"]
						tasknames = set(tasknames)
						view_totalscore_flag = not tasknames
						scores = []
						error_message = ""
						try:
							with open(os.path.join('..','etc','score.txt')) as f:
								for score_line in f:
									score_m = re.match(r'([^\s]+)[\s]*\(([0-9]+)\)[\s]*:.*', score_line)
									if score_m:
										namepart = score_m.group(1)
										scorepart = score_m.group(2)
										if view_totalscore_flag or namepart in tasknames:
											tasknames.discard(namepart)
											scores.append(int(scorepart)) 
							if tasknames:
								for taskname in tasknames:
									error_message += "taskname '{}' is not found.".format(taskname)
								raise Exception
							line = re.sub(r'\{score\s?.*?\}', str(sum(scores)), line)
						except Exception as e:
							line = re.sub(r'\{score\s?.*?\}', str(error_message), line )
						
					new_lines.append(line)
				return new_lines
				
		def add(p):
			md.preprocessors.add(p.__name__, p(md), '>normalize_whitespace')
		add(SamplePreprocessor)
		add(FigurePreprocessor)
		add(ScorePreprocessor)

# converter
def convert(html):
	# convert $ to var tag: $fomula$
	def convert_var(html):
		return re.sub(r'\$(.*?)\$', r'<var>\1</var>', html)

	# to support '--------' for headline
	def fix_h2_to_h3(html):
		return re.sub(r'(?s)<h2>(.*?)</h2>\n', r'<h3>\1</h3>', html)

	def fix_pre(html):
		return re.sub(r'(?s)<pre><code>(.*?)</code></pre>',
					  r'<pre>\1</pre>', html)

	def convert_section(html):
		sec = re.findall(r'(<h3>.*?(?=<h3>|\Z))', html, re.DOTALL)
		sec_wrap = u'\n<div class="part">\n<section>\n{}</section>\n</div>\n'
		sec = map(lambda s: sec_wrap.format(s), sec)

		html = re.search(r'(.*?(?=<h3>|\Z))', html, re.DOTALL).group(0)
		hr = '\n<hr />\n'
		html += sec.pop(0)    				# statement
		html += sec.pop(0)						# constraints
		if len(sec) % 2 == 1:
			html += sec.pop(0)					# scoring
		html += hr + '\n<div class="io-style">'
		html += sec.pop(0)						# input
		html += sec.pop(0)						# output
		html += '</div>\n'
		for s_in, s_out in zip(sec[::2], sec[1::2]):
			html += hr
			html += s_in						# sample input
			html += s_out						# sample output
		return html

	def wrap_lang(html):
		return u'<span class="lang-{}">\n{}</span>\n'.format(CURRENT_LANG, html)

	html = convert_var(html)
	html = fix_h2_to_h3(html)
	html = fix_pre(html)
	html = convert_section(html)
	html = wrap_lang(html)
	return html

# auto encoding
def conv_encoding(filename):
	with open(filename) as f:
		data = f.read()
	
	lookup = ('utf_8', 'euc_jp', 'euc_jis_2004', 'euc_jisx0213',
			'shift_jis', 'shift_jis_2004','shift_jisx0213',
			'iso2022jp', 'iso2022_jp_1', 'iso2022_jp_2', 'iso2022_jp_3',
			'iso2022_jp_ext','latin_1', 'ascii')
	encode = None
	for encoding in lookup:
		try:
			data = data.decode(encoding)
			encode = encoding
			break
		except:
			pass
	if isinstance(data, unicode):
		return data,encode
	else:
		raise LookupError

# main
def main():
	if len(sys.argv) < 2:
		sys.stderr.write(usage[1:])
		exit(-1)

	result = '<span class="lang">\n'
	for i in range(1, len(sys.argv)):
		text, _ = conv_encoding(sys.argv[i])
		detect_lang(text)
		html = markdown(text, extensions=[
						'markdown.extensions.fenced_code',
						'markdown.extensions.tables',
						 MyExtension()])
		result += convert(html)

	result += '</span>'
	print result.encode('utf-8')

if __name__ == '__main__':
	main()
