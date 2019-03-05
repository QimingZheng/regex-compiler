﻿/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Parser::ParsingXml.parser.txt

This file is generated by: Vczh Parser Generator
***********************************************************************/

#include "../Parsing.h"
#include "../ParsingDefinitions.h"
#include "../ParsingAutomaton.h"
#include "ParsingXml_Parser.h"

namespace vl
{
	namespace parsing
	{
		namespace xml
		{
/***********************************************************************
ParserText
***********************************************************************/

const wchar_t* const parserTextBuffer[] = {
  L"" L"\r\n"
, L"//////////////////////////////////////////////////////////////////" L"\r\n"
, L"// AST" L"\r\n"
, L"//////////////////////////////////////////////////////////////////" L"\r\n"
, L"" L"\r\n"
, L"class Node" L"\r\n"
, L"{" L"\r\n"
, L"}" L"\r\n"
, L"" L"\r\n"
, L"class Text : Node" L"\r\n"
, L"{" L"\r\n"
, L"\ttoken content;" L"\r\n"
, L"}" L"\r\n"
, L"" L"\r\n"
, L"class CData : Node" L"\r\n"
, L"{" L"\r\n"
, L"\ttoken content (XmlUnescapeCData);" L"\r\n"
, L"}" L"\r\n"
, L"" L"\r\n"
, L"class Attribute : Node" L"\r\n"
, L"{" L"\r\n"
, L"\ttoken name\t\t\t\t\t\t\t\t\t@Color(\"AttName\");" L"\r\n"
, L"\ttoken value (XmlUnescapeAttributeValue)\t\t@Color(\"AttValue\");" L"\r\n"
, L"}" L"\r\n"
, L"" L"\r\n"
, L"class Comment : Node" L"\r\n"
, L"{" L"\r\n"
, L"\ttoken content (XmlUnescapeComment);" L"\r\n"
, L"}" L"\r\n"
, L"" L"\r\n"
, L"class Element : Node" L"\r\n"
, L"{" L"\r\n"
, L"\ttoken name\t\t\t\t\t\t\t\t\t@Color(\"TagName\");" L"\r\n"
, L"\ttoken closingName\t\t\t\t\t\t\t@Color(\"TagName\");" L"\r\n"
, L"\tAttribute[] attributes;" L"\r\n"
, L"\tNode[] subNodes (XmlMergeTextFragment);" L"\r\n"
, L"}" L"\r\n"
, L"" L"\r\n"
, L"class Instruction : Node" L"\r\n"
, L"{" L"\r\n"
, L"\ttoken name\t\t\t\t\t\t\t\t\t@Color(\"TagName\");" L"\r\n"
, L"\tAttribute[] attributes;" L"\r\n"
, L"}" L"\r\n"
, L"" L"\r\n"
, L"class Document : Node" L"\r\n"
, L"{" L"\r\n"
, L"\tNode[] prologs;" L"\r\n"
, L"\tElement rootElement;" L"\r\n"
, L"}" L"\r\n"
, L"" L"\r\n"
, L"//////////////////////////////////////////////////////////////////" L"\r\n"
, L"// Lexer" L"\r\n"
, L"//////////////////////////////////////////////////////////////////" L"\r\n"
, L"" L"\r\n"
, L"token INSTRUCTION_OPEN = \"/</?\"\t\t\t@Color(\"Boundary\");" L"\r\n"
, L"token INSTRUCTION_CLOSE = \"/?/>\"\t\t@Color(\"Boundary\");" L"\r\n"
, L"token COMPLEX_ELEMENT_OPEN = \"/<//\"\t\t@Color(\"Boundary\");" L"\r\n"
, L"token SINGLE_ELEMENT_CLOSE = \"///>\"\t\t@Color(\"Boundary\");" L"\r\n"
, L"token ELEMENT_OPEN = \"/<\"\t\t\t\t@Color(\"Boundary\");" L"\r\n"
, L"token ELEMENT_CLOSE = \"/>\"\t\t\t\t@Color(\"Boundary\");" L"\r\n"
, L"token EQUAL = \"/=\";" L"\r\n"
, L"" L"\r\n"
, L"token NAME = \"[a-zA-Z0-9:._/-]+\"\t\t\t\t\t\t\t\t@ContextColor();" L"\r\n"
, L"token ATTVALUE = \"\"\"[^<>\"\"]*\"\"|\'[^<>\']*\'\"\t\t\t\t\t\t@ContextColor();" L"\r\n"
, L"token COMMENT = \"/</!--([^/->]|-[^/->]|--[^>])*--/>\"\t\t\t@Color(\"Comment\");" L"\r\n"
, L"token CDATA = \"/</!/[CDATA/[([^/]]|/][^/]]|/]/][^>])*/]/]/>\";" L"\r\n"
, L"token TEXT = \"([^<>=\"\"\' /r/n/ta-zA-Z0-9:._/-])+|\"\"|\'\";" L"\r\n"
, L"" L"\r\n"
, L"discardtoken SPACE = \"/s+\";" L"\r\n"
, L"" L"\r\n"
, L"//////////////////////////////////////////////////////////////////" L"\r\n"
, L"// Rules" L"\r\n"
, L"//////////////////////////////////////////////////////////////////" L"\r\n"
, L"" L"\r\n"
, L"rule Attribute XAttribute = NAME:name \"=\" ATTVALUE:value as Attribute;" L"\r\n"
, L"rule Text XText = (NAME:content | EQUAL:content | ATTVALUE:content | TEXT:content) as Text;" L"\r\n"
, L"rule CData XCData = CDATA:content as CData;" L"\r\n"
, L"rule Comment XComment = COMMENT:content as Comment;" L"\r\n"
, L"rule Element XElement = \"<\" NAME:name {XAttribute:attributes} (\"/>\" | \">\" {XSubNode:subNodes} \"</\" NAME:closingName \">\") as Element;" L"\r\n"
, L"rule Node XSubNode = !XText | !XCData | !XComment | !XElement;" L"\r\n"
, L"rule Instruction XInstruction = \"<?\" NAME:name {XAttribute:attributes} \"?>\" as Instruction;" L"\r\n"
, L"rule Document XDocument = {XInstruction:prologs | XComment:prologs} XElement:rootElement as Document;" L"\r\n"
};
const vint lengthTextBuffer[] = {
  2, 68, 8, 68, 2, 12, 3, 3, 2, 19, 3, 17, 3, 2, 20, 3, 36, 3, 2, 24, 3, 40, 63, 3, 2, 22, 3, 38, 3, 2, 22, 3
, 40, 45, 26, 42, 3, 2, 26, 3, 40, 26, 3, 2, 23, 3, 18, 23, 3, 2, 68, 10, 68, 2, 55, 55, 58, 58, 50, 51, 21, 2, 58, 65
, 75, 63, 56, 2, 29, 2, 68, 10, 68, 2, 72, 93, 45, 53, 134, 64, 93, 103
};
const vint lengthTextBufferTotal = 2487;

			vl::WString XmlGetParserTextBuffer()
			{
				vl::collections::Array<wchar_t> textBuffer(lengthTextBufferTotal + 1);
				wchar_t* reading = &textBuffer[0];
				for(vint i = 0; i < sizeof(parserTextBuffer) / sizeof(*parserTextBuffer); i++)
				{
					memcpy(reading, parserTextBuffer[i], lengthTextBuffer[i] * sizeof(wchar_t));
					reading += lengthTextBuffer[i];
				}
				*reading = 0;
				return &textBuffer[0];
			}

/***********************************************************************
SerializedTable
***********************************************************************/

const vint parserBufferLength = 4440; // 18926 bytes before compressing
const vint parserBufferBlock = 1024;
const vint parserBufferRemain = 344;
const vint parserBufferRows = 5;
const char* const parserBuffer[] = {
"\x00\x0E\x00\x02\x83\x80\x07\x7D\x00\x82\x03\xFF\x45\x08\x82\x83\x86\x81\x21\x6F\x6C\x2F\x32\x37\x84\x87\x02\x86\x00\x17\x82\x81\x24\x3C\x3A\x27\x30\x6D\x65\x06\x98\x8A\x80\x8E\x86\x00\x10\x92\x94\x98\x88\x04\x97\x80\x8E\x74\x56\x21\x2C\x35\x3A\x91\x8A\x84\x25\x8C\xA7\x89\x93\x8F\x98\x82\x8D\x08\xC0\x94\x21\x37\x37\x8D\x91\x91\x0C\xB9\x88\x9B\x91\x8D\x9C\x8C\xA0\x3F\x83\x83\xA5\xA0\x96\x98\x93\x93\x04\xCC\xAA\x9E\x93\x80\xA9\xAE\xA9\x44\xC6\x96\xA9\xA8\xAB\x82\xAC\xA7\x0C\xAD\xA9\xA3\x82\x27\x35\x3A\x37\x64\x61\x32\x39\x38\xA0\x9D\xB3\x86\x03\xBC\xAB\x8B\xBC\xB8\x01\xB7\xB7\x71\xF3\xB5\xA4\x8A\xA1\xAD\xBD\xA6\x7B\x88\xAA\xAA\xCC\xB6\xB4\xB8\xB9\x74\xDC\x82\x85\xC6\xB7\xC3\xAC\x97\x7D\xFF\x8F\xC2\xC2\xCD\x83\xBA\x00\x67\x89\xC4\x8B\xC3\xD5\xC4\xC0\xC8\x83\x89\x9F\xC1\xDD\xCC\xD3\x81\xC5\x9A\x81\xD1\xC4\x9C\x00\x8D\xDB\x87\x6F\x6E\x34\x25\x38\x3C\x3A\xBC\x8C\x05\x9D\xFF\x77\xD8\x84\xE0\x88\xDD\xBC\xBE\xC8\xC0\xE9\xD3\xCB\xD4\xCB\x68\xC1\x8F\xA7\xCD\x31\x92\xDC\xD7\x02\x89\x18\x9A\xEB\x8D\x8E\x39\x34\x62\x75\x3B\xDF\x74\xF5\xF0\xF3\xE7\x0F\xC4\x21\x34\x31\x36\xF2\xF2\xAF\x02\xC0\x90\x95\xE5\x32\xDE\xF7\xF2\xD8\x80\x0B\xC4\x2F\x33\x31\x3A\xEB\x74\x37\x74\x78\x7C\x19\x43\x45\x10\x1B\x65\x00\x82\x83\x3F\x0B\x18\x4D\x82\x40\x49\x2E\x13\x1C\x1D\x72\x35\x13\x18\x1D\x69\x39\x6B\x80\x01\x18\x5C\x82\x42\x13\x6F\x24\x12\x4A\x80\x1E\x88\x45\x88\x15\xC9\x4B\x8D\x03\x76\x2C\x9D\x74\x84\x78\xE2\x65\x15\x88\x41\x25\xAE\x15\x54\x70\xDC\x48\x49\x8C\x4C\xDF\x61\x7B\x6C\x7A\x00\x36\x13\x4D\x4D\x9D\x40\x93\x12\x7A\xEC\x44\x80\x53\x18\xB9\x7B\x66\x7E\x80\x4A\x94\x70\x81\x94\x02\x4C\x98\x73\x93\xF7\x79\x7B\x7D\x7F\xFF\x75\x74\x1C\x95\x00\x30\x12\x1D\x53\x67\x33\x1B\x82\x96\x03\x7C\x7E\x7C\x80\x0F\x88\x4D\x9B\x98\x6F\x34\x17\x81\x82\x5E\x8B\x80\x9B\x9C\x00\x8A\x08\x46\x9E\x02\x6B\x7F\x8A\x8F\x65\x26\x90\x97\x74\x02\x78\x9E\x95\x9B\x04\x6D\x93\x1A\x44\x73\x29\x1E\x18\x55\x21\x43\x04\xA2\x74\x85\x88\x80\x83\x8C\x03\x75\x85\x56\x00\x93\x91\x55\xA4\x9D\xD7\x58\x60\x03\x1C\x75\x22\x10\x8A\x88\x82\xB7\x78\xA3\x40\x6D\x91\x83\x85\x85\x17\x99\x8E\x18\x9F\x08\x74\xAE\x9D\x8F\x31\xA9\xAE\x7B\xAA\x02\x6D\xA2\x84\x85\x16\x98\x89\x6C\xA6\x02\x5A\xA1\x48\xB1\x00\x08\xB7\x89\x72\x60\x96\x9E\x91\x80\x02\x90\x08\x45\x0C\x18\x52\xB0\x73\xB5\x38\x4B\x82\x80\xB6\x49\x5A\xB7\x7C\xB7\xD9\x9E\xB6\x78\xB8\x84\x62\xB6\x7A\xB5\x08\x68\xB9\x12\x13\x53\x14\x12\x15\x15\x43\x14\x19\x13\x13\x4E\x1F\x1F\x10\x14\x45\x0E\x1A\xB3\x40\x2F\x3C\x0F\x0B\x0F\xC0\x5F\x61\x04\x46\x03\xD0\x8C\xBA\xBB\xF0\xB2\xB4\xBF\x17\x43\x0C\x1F\x13\x14\x45\x3B\xB2\x43\xBF\x2F\x3E\x0D\x66\x01\x18\x54\x09\xC5\x5E\x4F\x0D\x10\x14\x13\x45\x18\x1F\x15\x11\x20\xCD\x19\xBC\x15\xF6\xB8\xBA\xBD\x87\xFC\xBE\xBF\x08\xA7\x16\x5B\xCC\x42\xC6\x02\x53\x1B\xBB\x11\x20\xE3\xC5\xCB\xC9\x0C\xCE\xC0\xC6\xC4\x00\x2F\x02\xD2\x0F\x92\xBD\x54\x40\x71\x47\xC6\x8B\xCE\x13\x28\xF7\xB9\xBC\xCC\x08\x50\xDD\xBC\xB2\x39\x84\x4B\x88\x43\x57\xC0\x04\xC9\x11\x26\xCC\xDD\xCF\xC3\x45\x10\xD4\x42\xD4\x3E\x1F\x64\xAE\x61\x3A\x46\x81\x15\x15\x41\x0C\x12\xDB\x40\x52\xFD\x08\xC5\xB7\xF7\x40\xDE\x11\x10\x26\xC5\xC8\x42\xDE\x5B\x21\x1D\x0A\x1E\x41\x2D\x0A\x14\x0C\x2D\x39\x0A\x0E\x0B\x5F\x2F\x0D\x09\x17\x2B\x04\x8C\xAE\x7E\xA2\x81\x14\x14\x15\x56\x2D\xD5\x15\x11\x13\x18\x49\xE6\x40\x22\x1B\x1E\x14\x0F\x3E\x22\x0D\x16\x0A\x22\x3C\x17\x0A\xE7\xA0\xE7\x03\xEB\x09\xF9\x48\xDF\x55\xCC\x0F\x5D\xCD\xD4\x15\x22\x18\x45\xEF\xC4\xFE\xA1\x0D\x09\x0B\x28\x1E\xEA\xE2\x0F\x5D\x3C\x1D\x0A\xEF\x2D\x00\xF2\xF3\xF0\x5E\x00\xF9\x0A\x0A\xBB\xD5\xC5\xD7\x40\x59\xE8\xDB\x51\x5E\x44\x12\xE1\x10\x0B\x18\x58\xF8\xEF\x0B\x21\x2F\x0B\x17\x91\xD6\xDE\xFD\xEE\x17\x2F\x1D\x11\xF1\xF9\xBE\xE6\xFC\x1D\xF9\xE8\xC9\xFD\x17\xF2\xEC\xDD\x15\xC7\xD9\x09\x64\x8C\xCA\x40\x54\x21\xC4\x14\x09\x18\x7C\xF2\x43\xF8\xA0\x7D\x06\x08\x27\x00\x05\x17\x32\x0F\x05\x6E\x0F\x04\x7B\x7F\x61\x71\xC1\x45\x77\x70\x89\x6B\x71\x0A\x2B\x0C\x0F\xD2\x67\x07\x71\x0B\x45\x4A\x49\x03\x23\x0A\x28\x01\x0B\x08\x45\x05\x68\x42\x22\x8F\x05\x39\x2B\x06\x75\x93\x22\x40\xB5\x0C\x24\x7E\x81\x34\x50\x0B\x3C\x50\x47\x6E\x34\x68\x20\x1A\xB0\x86\x3B\x32\x85\x0E\x0B\x52\x0F\x0D\x38\x53\x0C\x3D\x72\x14\x0F\x03\x18\x23\x88",
"\x81\x00\x08\x04\x24\x1C\x07\x0D\xFF\x41\x46\x1F\x2D\x80\x00\x2F\x91\x84\xA0\x68\x54\x20\x74\x4B\x88\x57\xBB\x2E\x07\x0F\xF2\x24\x0F\x80\x0C\x26\x8B\x00\x07\x8A\x12\xD2\x8D\x89\x27\x91\x88\x87\x80\x48\x84\x00\x44\x37\x8B\x1C\xAE\x01\x06\x3C\x18\x21\x1C\x82\x23\x8C\x34\x8D\x8A\x07\x20\x17\x6E\xC9\x20\x08\x8E\x1B\x61\x27\x88\x22\x02\x80\x08\x12\x74\x72\xCB\x45\x0C\x8F\x20\x02\x48\x4D\x65\x00\x05\x30\x33\x0B\x90\x76\x9B\x36\x19\x83\x2D\x8D\x34\xB6\x34\x92\x64\x99\x8A\x0C\x73\x88\x20\x4E\xB5\x8C\x89\xBB\x3E\x04\x1E\xFA\x87\x91\x3E\x95\x28\x04\x81\x82\x07\x11\x84\x95\x72\x26\x17\x70\x91\x8A\x95\x25\x23\x8F\x99\x93\x32\x13\x92\x20\x95\x91\x46\x1A\xEC\x85\x96\x17\x33\x04\x93\x04\x3E\x91\x2E\xA1\x93\x94\xBC\x65\x90\x04\x7E\x8C\x91\x2A\x83\x93\x73\x56\xAF\x90\x8F\xB1\x8C\x92\x23\x90\x90\x95\x32\x00\x0F\x96\x00\x03\x99\x19\x12\x08\x22\x6E\xB8\x95\x97\x3C\x91\x4D\x11\x70\x25\x88\x84\x25\x99\x89\xDA\x9E\x04\x08\x40\x08\x4C\x5C\x86\x52\x37\xD8\x98\x0B\x3B\xF4\x0E\x04\x19\x0E\x02\x32\xF7\x94\x8E\x3C\x96\x5E\x4A\x51\xA8\x94\x07\x22\x19\x8E\x31\x88\x99\x99\x23\xBB\x08\x04\xDA\x88\x93\xAD\x39\x8F\x91\x3E\x20\x00\x05\xA8\x95\x61\x40\xFC\x08\x95\xD0\x60\x07\xA0\x58\x13\x09\xA9\x27\x5C\x90\x3C\xA4\x56\x54\x21\x41\x50\x08\x0E\xA2\x04\x7F\x41\xA4\x94\x88\x8B\x53\x1B\x0D\x5F\x50\xB1\x15\xA1\xA0\x29\x13\x94\x08\x73\x9D\x00\x05\x0A\x8B\x9E\xFE\x85\xA7\x49\x83\xA6\x95\x90\x2B\x98\xA3\xB5\x8A\xA1\x24\xA2\xAE\xA0\x88\xA2\x02\xA2\x20\x14\xA2\x08\x16\xA8\xA2\x8D\xA0\xA2\x44\x88\x9F\xA0\x47\x8D\xAF\x9F\x17\x3B\xA3\x8F\x78\x8A\xA4\x4B\x90\x5A\x98\x8B\xB1\xA3\x9A\xF3\x9B\x94\x25\xAE\x50\x59\x58\x79\x30\x8C\x04\x20\x8C\x16\x64\xA0\x56\x61\x6E\x0D\x9E\xA4\x18\x21\x5C\xFA\x9C\xAD\x60\x72\x51\xA7\x3C\x1F\x07\x55\xC7\x95\xA1\x8B\x88\xA1\xA8\x78\x8B\xA0\xA0\x54\xA2\x05\x1F\x16\xA3\x9A\x75\xA6\xAE\x1B\x35\xAA\x89\xC4\xAE\xA8\xAF\x7A\xA2\xA0\x56\xC8\x97\x94\x20\x00\xAB\xA8\x42\xB5\x98\x61\x86\xB1\xA0\xC4\xBF\x55\xAD\xB2\x4D\x9D\x36\xF3\x91\x9F\x79\xAE\x04\x06\xF9\x88\x21\x6A\xB7\xAC\x9E\xDD\x38\xAB\xAF\x04\xA7\x97\x65\xD5\x99\xB2\x2C\x84\xAF\xA1\x11\xB6\xA2\x52\xA1\x76\xA0\x84\x8E\xAC\xA3\x51\xBB\xA1\x48\x84\xB6\xA4\xC9\x87\x9A\xAB\x8E\x5C\xAB\x4B\xA0\x0F\xAB\x47\xB4\xA6\xA6\xFB\x80\x54\x1D\x2F\xB6\xB9\xD8\xBE\xA3\xB6\xB6\xB5\xB4\x43\xA3\xA8\xB7\xA3\xBA\xB3\xB9\x96\xBE\xB6\x70\xD0\xAE\xA3\xF1\xB7\xB5\xA4\x56\xB5\xB9\x56\x8C\x59\xB8\x97\x8B\xA8\xA6\x32\xB3\x9E\x68\xD1\xB9\x4F\x3D\x54\x96\xB4\x33\x06\x10\x46\x7A\xBA\x9E\x9C\xB8\x8A\xA7\xEA\xB4\xB3\x75\xFF\xA8\xB3\xC0\x83\xAC\xAA\x46\xA8\xAB\x6E\x81\xAD\xA8\xF3\x81\xBF\xA9\xE7\xA5\xB8\x4A\xEB\xBB\xA5\xF6\xA7\x97\xBD\xCC\xB1\xBD\x6B\xF4\x00\x08\xB1\xB8\x96\xB1\xB2\x48\xAF\x40\x6A\xA0\xC5\xDC\x3E\x91\x0A\x18\x28\xC4\x5D\x9F\xB6\xAF\xDC\x10\xB0\xB6\x3D\xAC\x90\x76\xB9\x8A\xBB\xC1\x9C\xBD\xB0\x87\xAF\x91\x89\xEE\x0C\x9C\x51\x74\xBE\x4B\xA5\xBB\xC2\x0B\x36\x0C\xBE\x84\x05\xCC\xB5\xD2\xB4\xBB\x84\x82\xC2\xC6\x02\xF4\xB6\xC0\x9A\xBC\xB9\x82\xDF\xB8\xC3\x06\xD0\xC7\xC1\x53\xB7\xC6\x49\xC7\x8B\xC8\xE4\xAD\xA7\xC2\x5E\xBA\xC2\x74\xC0\x48\x0A\x14\x7D\x30\x4C\x65\xC9\x3B\x1B\xD8\x08\x22\x36\xFA\x9E\xCC\xD3\xA5\x9B\x64\xCE\x5E\x4B\xA4\xB3\xA3\x6D\x6D\x69\xA5\x93\x75\xC4\xA2\x56\x86\x92\xCF\x57\x54\x0E\x9D\xF9\x75\xCC\x40\xCF\x5A\xA6\x70\xC0\x0B\xDC\x08\x2B\xD0\x2C\x07\x4B\x3D\x61\x13\xBF\xA3\xEC\x3F\x8D\x11\x18\x26\xD2\xFA\x93\xD1\x18\x7E\x90\x7C\x2A\x01\x0E\xD0\x75\xD3\x9A\xA6\xBD\xCD\x2E\x47\xEF\x0C\x3E\xF0\x96\xBC\x2E\xF3\x30\x41\x37\xA9\x00\x23\xAF\xD9\xD3\xA9\x80\x4C\xD2\xD9\x67\x60\xD4\xBA\x32\xA4\xAB\xDE\x44\xD4\xC6\x2E\x9B\xC3\x41\xD2\xBB\x1B\xC5\xC4\x21\x23\xFF\xC6\xB5\xFF\xA0\xA0\x97\xBC\xAC\xC8\xBF\x89\xA0\xCA\xB6\xA8\xC1\x6E\x93\xAB\xB8\x2B\xC0\xBD\xBC\x10\xC4\xB9\x7A\xDD\xCC\xBD\x2F\xFE\xA0\xC3\xCD\xB3\xA7\x86\xF3\xB3\x9E\x2A\x83\x26\x8A\xA6\xA1\x9E\x9C\x70\x21\x7A\xE8\x43\x20\x9D\x38\xAB\x9F\x7C\xBF\xB1\xA5\x78\xB4\xDA\x44\x6F\x95\x04\x46\x7A\xDA\x9F\x7B\xE5\x0E\x9F\x21\x09\xCD\x6F\x76\xC1\xE0\x4D\xC4\xE6\xD4\xA8\xC2\xD0\x45\x81\xE3\x9E\x20\x0F\x79\x3B\x94\x8A\x4D\x97\x3A\x3F\x71\x36\x58\x0A\xE2\xAD\xD1\x04\x18\x18\x2B\xE2\x7D\x98\xE5\x9F\x78\x98\xA3\x8E\x88\x92\x4C\x32\x4F\x94\xA2\x08\xE0\x40\xC9\xE3\x42\x23\x32",
"\x5C\xBF\xD8\x82\xD8\x8C\x9C\x72\x4B\xC2\x99\x9F\xE2\x37\x1D\xD7\x93\x87\xAC\xCA\xB0\x1A\x84\x26\x86\x3B\xDB\x85\x0F\xEB\xD4\x0C\xBD\x44\x22\x6F\xE8\x9B\xC6\x3A\x8E\xED\x45\x6C\xB7\xE4\x0E\x15\xF1\xE0\x97\x2D\xD2\x07\x8E\xC8\x26\xEA\x4A\x8F\xEA\x3F\xE1\xBB\xAC\x9E\xEE\xAB\xE5\x26\xF6\xCD\xCA\xF5\xC8\x8F\x92\xED\xE4\xAA\x30\xE8\x93\xCC\xF3\x96\xE7\xA9\xDE\x4C\xDC\xC0\xCA\xD7\x68\xC2\xC7\x06\x62\xC3\x26\xD8\xFE\xBF\x9C\x8C\xCD\xD3\xC6\x40\x75\xC1\x57\x52\xD3\xDA\x9D\xD5\xC2\xBD\x2B\xD8\xD9\xCB\x24\xB2\xC0\xB3\xDE\xCC\xAA\x40\xA1\xC8\xAC\x1B\xC4\xCC\x9C\xED\xD2\x21\xAC\x42\xE4\x9E\xEA\xC3\x9C\x19\x58\x98\x9C\x38\xCB\xEB\xD1\x04\x2D\xD2\xA6\xA2\xC2\x20\xB5\x9A\xD2\xE8\xE2\x90\x2D\xD4\x82\x28\x9C\x4D\xCB\xEA\xD2\xB3\xDE\x4A\xB9\x82\x26\x8B\x5D\xFA\x30\xF5\x44\xF4\xF0\x00\x59\x6D\xF5\xD8\xEE\xB2\xDE\x3E\xDE\xDF\xEC\x80\x06\x8A\x7F\xF8\xF2\xF3\xBA\xFC\xF6\x12\xFE\xDB\xE9\x87\xC0\x01\x47\x17\xEE\xEE\x6E\x46\xE3\x20\xBD\x51\xFB\x4D\x5E\x47\xF8\x5C\x24\xF0\x21\x77\xD9\xEA\xFA\xD3\xAB\x9E\x87\xD9\x9B\xC6\xEE\xE4\xC6\xEB\xB2\x4F\x8E\x8A\x88\x2B\xFD\xC6\xA8\xFE\xC5\xC9\xDA\xAF\xB2\x93\xB9\x98\x67\xC0\xB5\x91\x07\xD7\xC4\x67\xB2\xAB\xC6\xC9\xC9\x3D\x9C\x04\x15\x4E\x97\x78\x7B\x5B\x41\x44\xD8\x47\x44\x9D\x79\x1C\x65\x3B\x41\xB8\x40\x67\xAB\x79\x4D\x70\x6A\x45\x40\x44\x07\xCE\x79\x23\x62\x47\x79\x3E\x00\x7A\x03\x12\x7A\x48\x21\x06\xC3\x75\x7B\x1D\x84\x80\x13\x8F\x80\x08\x8A\x44\xAE\x7A\x81\x02\x1C\x81\x90\x63\x7E\x8E\x61\x82\x05\x84\x07\x07\x80\x02\x26\x8D\x81\x3E\x00\x7B\x09\x7E\x4D\x08\x18\x83\x63\x77\x7B\xEA\x6F\x82\xC9\x73\x10\x25\x8B\x83\xD3\x56\x83\x00\x26\x7E\x94\x46\x7B\xF4\x4F\x82\xE3\x77\x81\x48\x85\x83\x3E\x63\x4F\x38\x84\x10\x3A\x89\x6E\x43\x7E\x83\x18\x19\x35\x41\x88\x53\x70\x72\x5D\x46\x8F\x6B\xC2\x6A\x84\x3A\x71\x46\x32\x80\x73\x4E\x85\x6A\xFE\x61\x85\x03\x1A\x83\xC6\x7D\x83\x13\x8F\x83\x46\x48\x44\xCB\x76\x5E\x65\x8E\x6B\xD9\x4E\x6F\x5D\x85\x87\xE6\x52\x81\x5C\x4B\x84\x63\x8C\x7C\x2C\x8B\x63\x16\x08\x11\x81\x8B\x73\xAF\x2D\x62\x6F\x5C\x86\x5C\x44\x7D\x02\x1A\x37\x41\x8A\x74\x7F\x8F\x7E\x6E\x08\x86\x02\x1A\x83\x41\x7F\x82\x1F\x80\x84\x63\x8A\x74\x15\x82\x75\xD8\x7A\x1B\x9B\x38\x10\x9F\x87\x7D\x13\x78\x79\x55\x83\x81\x77\x81\x84\x5A\x7B\x89\xB8\x4F\x74\x00\x83\x10\x02\x8F\x74\x7A\x81\x44\x6E\x82\x86\xDF\x7D\x89\xD3\x51\x4F\xB5\x4C\x82\xBD\x44\x03\xC0\x43\x10\xC2\x45\x4B\xFE\x4B\x64\xF5\x7B\x4C\x7E\x6E\x4A\xC7\x41\x4D\x32\x55\x4B\x40\x0E\x7F\x67\x63\x29\x03\x82\x03\x6E\x68\x10\xD1\x8A\x44\x9E\x72\x67\xC7\x5B\x67\xB9\x64\x51\x45\x08\x67\x4C\x08\x6B\x0A\x7C\x4C\x85\x46\x8C\xDE\x83\x68\xFA\x33\x8E\xD3\x49\x68\x28\x80\x00\x2A\x8C\x1E\x92\x61\x82\x32\x08\x69\x08\x10\x8F\x33\x80\x69\x9C\x65\x3D\x9E\x66\x8E\x8F\x43\x6A\x44\x80\x64\x72\x72\x84\xF5\x41\x6B\x08\x10\x90\x26\x8E\x7B\x71\x60\x02\x43\x06\x6B\x4C\x38\x8F\x06\x94\x90\xBD\x65\x1A\x5E\x85\x5F\x2C\x47\x5F\x42\x65\x03\x76\x72\x10\x78\x7B\x61\x4A\x6C\x6C\xF5\x7D\x77\x31\x2F\x77\xBB\x12\x6D\xDE\x54\x6D\x84\x79\x51\x0E\x67\x78\xC3\x5A\x65\xDB\x6B\x78\xDD\x6A\x5C\xE0\x62\x66\x00\x29\x73\x0C\x1C\x46\xE5\x78\x11\xE7\x75\x88\x8A\x57\x5A\xEB\x74\x10\xED\x7D\x75\x36\x9F\x58\xF1\x7B\x77\x1B\x9E\x64\xD9\x50\x6D\xDB\x54\x52\xFB\x7E\x59\x3D\x92\x2B\x4C\x7C\x10\xD0\x7F\x74\x0F\x82\x8A\xAD\x63\x03\x56\x74\x10\x58\x70\x95\x20\x7E\x6C\x23\x75\x76\x2C\x7F\x06\x2E\x78\x72\x48\x80\x76\x67\x7F\x72\x6C\x72\x73\x43\x7C\x76\xD3\x4F\x74\x0D\x93\x10\xB8\x83\x54\xAA\x80\x00\xB5\x44\x2E\xF5\x37\x1F\xCC\x84\x07\x40\x30\x67\xC0\x1C\x01\x24\x12\x20\xE9\x8B\x8E\x61\x06\x24\x1D\x80\x1C\x1E\x09\x97\x59\x2E\x63\x48\x80\x26\x48\x80\x1C\x20\x02\x98\xEE\x1B\x85\x53\x23\x29\xF3\x40\x1C\xB7\x31\x2E\x8B\x91\x7C\xE6\x56\x37\x21\x50\x1C\xFE\x32\x99\xE6\x1F\x88\x49\x99\x1B\x0F\x8B\x63\xC0\x16\x02\x8A\x96\x1E\x6D\x96\x95\xA1\x2D\x17\x4F\x70\x1C\x28\x03\x9A\xE5\x10\x01\x22\x49\x10\xC2\x10\x1C\x9D\x10\x97\xB4\x95\x9B\x38\x12\x1C\x8F\x3F\x36\xB6\x90\x00\x9D\x13\x9B\xF7\x36\x22\x03\x19\x4C\xC0\x1B\x96\xD5\x40\x97\xCD\x15\x10\x4F\x4F\x9A\xBB\x9B\x9C\x24\x12\x1C\x6A\x48\x2C\xB5\x9D\x9B\xB4\x90\x24\xD1\x43\x9C\xFD\x8F\x96\xB0\x9D\x9C\x0C\x8C\x9C\xBC\x9C\x9D\x10\x7C\x94\x2F\x13\x54\xD6\x91\x91\xDF\x43\x54\xFF\x0A\x9B\x05\x18\x9E",
"\x04\x22\x9B\x9D\x23\x10\xCA\x9B\x9B\x6D\x98\x9D\xE4\x95\x2B\x98\x43\x54\xE9\x8B\x9E\xB4\x94\x9C\xB6\x58\x9E\xE3\x94\x9F\x7D\x27\x60\xC0\x1C\x99\x65\x5E\x56\xE7\x98\x11\xE9\x8C\x9E\x0C\x19\x8E\xEF\x96\x9B\xF1\x92\x9E\x72\x74\x10\x67\x45\x4D\x7B\x9E\x9D\x50\x47\x9D\x43\x5C\x9F\x0F\xAA\x96\x03\x12\x58\xB9\x20\x1C\x8C\x9E\x25\x14\xA4\x2E\xC7\x9F\x0F\x04\x2E\x7C\x21\xA1\x1C\x24\x1E\x7C\xF9\x17\xA2\x23\xA9\x9B\x14\xA8\x9E\x9F\x17\xA0\xB4\x9F\xA1\xBA\x1E\x9B\x0C\x10\x34\xC2\x99\xA1\x2E\x45\x9F\xC5\x9C\x1C\xC2\x16\x36\x27\xAC\x2D\x2D\xA8\x11\x18\xA0\x97\x30\xAD\x9E\xBB\x92\xA0\xA0\x59\x1B\x36\xA0\x9C\x37\xA1\x9C\x37\x2A\xA3\x15\xA5\x9E\x3D\xAE\xA3\x24\x19\x8E\x8F\x3C\xA2\xC2\x19\x1F\xAD\x8B\x9B\x47\xA6\x34\xCB\x94\xA3\x74\x0F\x19\x25\x04\xA1\xF3\x66\x5E\x28\xA9\x14\x4F\x4A\x46\xB5\x9B\xA0\x9F\x1B\xA2\x33\xAF\x84\x91\x78\x11\x65\xAE\x9D\x67\xA0\x61\x4D\xAE\x29\x94\x20\x00\x74\x6A\x1B\x01\x3B\x9D\x97\x73\xA4\x31\x94\xA1\x6E\xA2\x2A\xCC\x92\xA6\x64\xA6\xA6\x94\x98\xA7\xB4\x9D\x2C\xD8\x84\x07\x7F\xA9\x36\x0D\x89\x22\xCE\x91\x86\xCC\x95\xA8\x60\xAB\x9B\x88\xA4\xA7\x8A\xA6\x86\xE6\x59\xA7\xAF\x3B\xA7\x7D\xA0\xA9\xDB\x92\x3D\x81\xA2\x1C\xBA\x7C\x7D\x6D\xA5\xAA\xAF\x1D\xA9\x74\x80\x73\x89\xA6\xA7\x8B\xAC\x51\xA0\xA1\x1F\x93\x23\xAA\x1E\xA4\x98\x04\x93\xA2\xDC\x7A\x7B\xAB\xA2\xA9\x74\x87\xA8\x72\xA3\x66\x9C\xA2\xAB\x9E\xAC\xA8\x70\x9E\xA8\x81\x60\x1C\x13\xAB\x6A\x1D\x83\xA2\x5D\xAB\x46\x84\xAC\xAA\x02\x10\xA7\x70\x9B\xA9\x0C\x15\xA7\xDC\x97\xA7\xB4\xAD\xA8\xB7\xAF\xA8\x91\xA3\x3D\x93\xAD\x1B\x69\xA7\x9B\xD5\x24\xA1\xB5\xA7\x2D\x77\x2B\x61\xB9\xA5\x6A\xF3\x4F\x0F\x0B\xA5\xA0\x0C\x12\x89\xD7\x2D\x19\x00\x94\x10\x0B\xA5\x9B\xEB\xA2\x5D\xED\xAF\xAA\xF3\x49\x8E\xF7\xA1\xA6\xC3\xA0\x20\xE9\xAF\x80\x6B\x7C\xAE\x4D\x74\x10\x4D\x90\x7E\xF2\xAB\x37\xB4\x9D\x19\xDA\xA8\xAF\x14\xAB\xAF\x00\x2D\xAF\x0E\x93\x77\xD2\x59\x8E\x11\xB2\xB0\xEE\xAB\x61\xF9\xAE\xAA\x17\xB4\x92\x10\x6D\xB0\x52\x8F\xB0\x32\x33\x42\x13\xBE\x98\x08\xB9\xA9\x90\x3F\x90\x5E\x29\x8E\x3E\x7C\xB1\xFE\xAB\x61\x05\xBE\x20\x03\x17\xB0\xFC\xA9\xB0\x03\x1B\xB0\xB6\x86\x9C\xC2\x1D\x19\x9F\x8C\x9C\xE9\xA0\x1C\x9F\x90\x89\x01\xA1\x86\x3C\x93\xA0\xB2\x24\xB2\x09\x18\x9E\x31\xB8\x2D\xF6\xA8\x11\x1F\xB0\x97\x45\xBD\x99\x6E\x07\xB4\x83\xA4\x88\x4A\xB9\x1B\x00\xB4\xA1\x4A\xA6\x88\x45\xAB\xA7\x7A\xA6\x76\x5C\x93\x07\x38\x2D\x74\xA6\x91\x20\x4E\xB6\xB2\x33\x32\xB5\x14\xA5\xB5\x5B\xB7\xB5\x96\xA3\x10\x32\x90\x89\x30\xBE\xB5\x48\xBB\x63\x61\xBA\xA7\x63\xBB\x95\x65\x27\xB6\xE0\x9B\x8A\xE0\x71\xA2\x82\xA8\x10\x15\x08\xAE\x18\x15\xB3\x0C\x1A\x28\x2B\x92\x16\x16\xBD\xAA\x2E\xBE\xA7\x84\x1F\xB3\x82\x88\xB8\xDE\x95\x97\xC9\x11\xAE\xA6\xA0\x67\x23\xA8\x9E\x8A\x85\xAF\xC5\xA8\xB2\x97\xBF\x9B\x76\x94\xAD\xA0\x14\x49\x70\x6A\xB1\x14\xA3\x97\x53\xBB\xAD\xB3\xA7\x99\x22\xA4\xB9\x0C\x17\x01\x96\xBC\x9D\x7E\x90\x69\xCC\xA6\xA0\x47\x8F\xAC\xC2\x1E\xB9\x6C\xB8\x10\x1B\xB2\x10\xAD\xB0\x2E\xB7\xBC\x1E\xB9\xB9\xA0\xBB\xB0\x69\xAA\xBE\x9D\xCD\xA9\x4D\x9A\x63\xBC\x32\xB1\xB2\xFE\x6E\xB3\xDA\x9C\x10\x18\x05\xBB\xCC\x96\x98\x04\x9F\xB8\xD5\xA7\x84\xBB\xA1\xAF\x6B\xB0\x97\x51\xBC\x10\xD0\xB8\x2D\xDA\xB9\x70\xDC\xBD\xB2\xCE\xB4\x90\x5D\xB6\xAC\xAF\xA8\x84\x7B\xB1\xAA\x7D\xB6\x72\x80\xBA\x23\x9C\x83\x8A\x4C\xBB\x88\xBF\xB4\x10\xC1\xB0\x00\xE5\xBA\xAE\x93\x27\x98\x86\xA0\xB9\xEB\xB9\x70\xCB\xBE\xBA\xA5\x68\x84\xFF\xB5\x9B\xDC\xA1\x52\xF9\xB0\x00\x4F\xB0\xBA\x6D\xB4\xBE\x29\xB0\x3B\x28\x1B\xBD\x03\xCD\xBD\xAB\x6C\xBE\x27\xB2\xAC\x09\xC4\x90\xF1\xB6\xAB\x16\xC4\xB6\x7F\xBA\xB3\xDF\x9E\x74\x83\xB4\xA1\x85\xB1\x7A\xD8\xB3\x10\xE9\xA8\xA3\x51\xAC\xB2\x8B\x10\x73\xDC\x93\xA2\x9D\x19\x01\x41\xA6\xAE\x49\x18\x9E\xD6\xA8\x10\xAD\x14\xA4\xBA\xBC\xB2\x0C\xCF\xBA\x22\x21\xC2\xEA\xB7\xB1\x52\x53\x5C\xE9\xB3\xC3\x8F\x91\xBB\xD5\xB8\x10\x1A\x0D\xC2\x9A\xA2\x2A\xA9\x96\xC2\xCF\x77\xBF\x15\xB9\xC3\x49\x12\x1C\xC8\x2B\x01\x52\xC7\xBA\x13\xCC\x9D\xA5\x95\xC5\xE5\xA4\x18\x5C\xAF\xC5\x9F\x11\xC1\xB5\x93\xC6\x29\xC3\x19\xA8\xA4\x93\x2F\xA6\xBA\x6A\xC4\x9B\x6C\xC6\x8B\xE9\xAA\xAC\xCF\x2B\xC4\xDE\xB8\xBE\xD8\x23\xA2\x6D\x9A\xC5\x80\xC1\xC8\x82\xCF\xC4\x84\x1F\x38\xF8\x92\xBE\x89\xB4\x9B\x30\xC1\x12\x58\xB5\x1C\x63\x56\xB4\xD9\x99\x14\xC0\x1D\x01\x83",
"\xC4\xB8\xC2\x1B\xA6\x5F\xC7\xC7\xDF\xAB\xAC\xA6\xB7\x12\xA7\xA4\x12\x8F\x3C\xA6\xFB\xBE\xC2\xDE\xA6\xC1\xB8\xAD\xC9\xA8\xB4\xA9\xB4\x13\xB7\xBB\x92\x9D\xC9\xAB\xC9\x79\xC8\xCA\xE3\xA4\xAA\xD0\xAC\xCA\xB6\x9E\xCA\xE4\x28\xC7\x20\xA2\xCB\x10\x8A\xCA\x92\xC8\x11\x1F\x05\xC9\x39\xCC\xAB\x57\x89\xC9\xA5\xC2\xAA\xE0\xA1\xC4\x8C\x69\xBC\xC6\xB3\xA2\xC0\x11\x02\xC2\xCA\xA5\x24\x19\xAA\xC6\xCF\xCA\xA6\xC9\xCC\x32\xCB\xC7\x59\xCE\xCC\x97\x61\xCD\xCB\x93\xA2\x67\xCE\xCD\x65\xC9\x10\xC0\x1D\xBF\xE2\xCD\xC7\x5B\xA4\x44\x68\xC1\xBA\x1E\xCF\xAA\xD3\xB3\xA2\x98\xCE\x9D\x5F\xA0\xBC\x20\xB4\xC0\x22\xBD\xAD\xD6\xC8\xCC\x9C\xC0\xAC\x9B\xBE\xCB\x38\x11\xCA\x71\xCC\xCF\x03\x16\xCE\x71\xA7\xAC\xF8\xC9\xCB\xB0\xCB\xCB\x02\xD8\x17\xB3\xC3\xA2\xE3\x7C\x9C\xF3\xCC\xBF\xF5\xCA\xC1\x78\x88\xAC\x08\xD7\xCD\xFB\xC2\xAE\x1A\xDF\xC9\x49\x14\xCD\xF2\xC6\xBA\x04\xD7\xAD\x44\xC5\x06\x9A\xC8\xD1\xB1\xC9\xCD\x1B\xC9\x70\xC4\xC8\x35\x01\xDA\xD1\x12\xDE\xBE\xD2\xBF\xA9\xC7\xCA\xA7\xA7\xC8\xBC\x36\xDE\xBC\xBC\xB4\x12\xD1\xA2\xCA\x46\xA0\xD2\x13\xDA\xBE\xF7\xC1\x52\x25\xDA\xCF\x27\xDE\xD2\x95\x1D\xD0\xB1\x98\x11\x27\x07\xCE\xE0\x23\xA2\x5D\xCC\xD4\x91\xC8\x13\xC0\x11\xB0\x50\xDA\xC3\x38\x1F\xD4\xDE\x9A\x41\x0C\x14\xD5\x0C\xA8\xB6\x64\xC0\xCE\xEA\xC9\xD5\xA6\xBC\xD5\x6B\xCE\xD5\x6D\xC3\xCE\x93\x1E\xD1\xDC\x91\xD1\x03\x14\xD6\x74\xC6\xD6\x76\xC3\xD3\xA1\xA5\xD3\xC1\xA6\xCF\x02\xC5\xD5\x78\xD0\xC8",
};

			void XmlGetParserBuffer(vl::stream::MemoryStream& stream)
			{
				vl::stream::MemoryStream compressedStream;
				for (vint i = 0; i < parserBufferRows; i++)
				{
					vint size = i == parserBufferRows - 1 ? parserBufferRemain : parserBufferBlock;
					compressedStream.Write((void*)parserBuffer[i], size);
				}
				compressedStream.SeekFromBegin(0);
				vl::stream::LzwDecoder decoder;
				vl::stream::DecoderStream decoderStream(compressedStream, decoder);
				vl::collections::Array<vl::vuint8_t> buffer(65536);
				while (true)
				{
					vl::vint size = decoderStream.Read(&buffer[0], 65536);
					if (size == 0) break;
					stream.Write(&buffer[0], size);
				}
				stream.SeekFromBegin(0);
			}
/***********************************************************************
Unescaping Function Foward Declarations
***********************************************************************/

			extern void XmlMergeTextFragment(vl::collections::List<vl::Ptr<XmlNode>>& value, const vl::collections::List<vl::regex::RegexToken>& tokens);
			extern void XmlUnescapeAttributeValue(vl::parsing::ParsingToken& value, const vl::collections::List<vl::regex::RegexToken>& tokens);
			extern void XmlUnescapeCData(vl::parsing::ParsingToken& value, const vl::collections::List<vl::regex::RegexToken>& tokens);
			extern void XmlUnescapeComment(vl::parsing::ParsingToken& value, const vl::collections::List<vl::regex::RegexToken>& tokens);

/***********************************************************************
Parsing Tree Conversion Driver Implementation
***********************************************************************/

			class XmlTreeConverter : public vl::parsing::ParsingTreeConverter
			{
			public:
				using vl::parsing::ParsingTreeConverter::SetMember;

				void Fill(vl::Ptr<XmlNode> tree, vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)
				{
				}

				void Fill(vl::Ptr<XmlText> tree, vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)
				{
					SetMember(tree->content, obj->GetMember(L"content"), tokens);
				}

				void Fill(vl::Ptr<XmlCData> tree, vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)
				{
					if(SetMember(tree->content, obj->GetMember(L"content"), tokens))
					{
						XmlUnescapeCData(tree->content, tokens);
					}
				}

				void Fill(vl::Ptr<XmlAttribute> tree, vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)
				{
					SetMember(tree->name, obj->GetMember(L"name"), tokens);
					if(SetMember(tree->value, obj->GetMember(L"value"), tokens))
					{
						XmlUnescapeAttributeValue(tree->value, tokens);
					}
				}

				void Fill(vl::Ptr<XmlComment> tree, vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)
				{
					if(SetMember(tree->content, obj->GetMember(L"content"), tokens))
					{
						XmlUnescapeComment(tree->content, tokens);
					}
				}

				void Fill(vl::Ptr<XmlElement> tree, vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)
				{
					SetMember(tree->name, obj->GetMember(L"name"), tokens);
					SetMember(tree->closingName, obj->GetMember(L"closingName"), tokens);
					SetMember(tree->attributes, obj->GetMember(L"attributes"), tokens);
					if(SetMember(tree->subNodes, obj->GetMember(L"subNodes"), tokens))
					{
						XmlMergeTextFragment(tree->subNodes, tokens);
					}
				}

				void Fill(vl::Ptr<XmlInstruction> tree, vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)
				{
					SetMember(tree->name, obj->GetMember(L"name"), tokens);
					SetMember(tree->attributes, obj->GetMember(L"attributes"), tokens);
				}

				void Fill(vl::Ptr<XmlDocument> tree, vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)
				{
					SetMember(tree->prologs, obj->GetMember(L"prologs"), tokens);
					SetMember(tree->rootElement, obj->GetMember(L"rootElement"), tokens);
				}

				vl::Ptr<vl::parsing::ParsingTreeCustomBase> ConvertClass(vl::Ptr<vl::parsing::ParsingTreeObject> obj, const TokenList& tokens)override
				{
					if(obj->GetType()==L"Text")
					{
						vl::Ptr<XmlText> tree = new XmlText;
						vl::collections::CopyFrom(tree->creatorRules, obj->GetCreatorRules());
						Fill(tree, obj, tokens);
						Fill(tree.Cast<XmlNode>(), obj, tokens);
						return tree;
					}
					else if(obj->GetType()==L"CData")
					{
						vl::Ptr<XmlCData> tree = new XmlCData;
						vl::collections::CopyFrom(tree->creatorRules, obj->GetCreatorRules());
						Fill(tree, obj, tokens);
						Fill(tree.Cast<XmlNode>(), obj, tokens);
						return tree;
					}
					else if(obj->GetType()==L"Attribute")
					{
						vl::Ptr<XmlAttribute> tree = new XmlAttribute;
						vl::collections::CopyFrom(tree->creatorRules, obj->GetCreatorRules());
						Fill(tree, obj, tokens);
						Fill(tree.Cast<XmlNode>(), obj, tokens);
						return tree;
					}
					else if(obj->GetType()==L"Comment")
					{
						vl::Ptr<XmlComment> tree = new XmlComment;
						vl::collections::CopyFrom(tree->creatorRules, obj->GetCreatorRules());
						Fill(tree, obj, tokens);
						Fill(tree.Cast<XmlNode>(), obj, tokens);
						return tree;
					}
					else if(obj->GetType()==L"Element")
					{
						vl::Ptr<XmlElement> tree = new XmlElement;
						vl::collections::CopyFrom(tree->creatorRules, obj->GetCreatorRules());
						Fill(tree, obj, tokens);
						Fill(tree.Cast<XmlNode>(), obj, tokens);
						return tree;
					}
					else if(obj->GetType()==L"Instruction")
					{
						vl::Ptr<XmlInstruction> tree = new XmlInstruction;
						vl::collections::CopyFrom(tree->creatorRules, obj->GetCreatorRules());
						Fill(tree, obj, tokens);
						Fill(tree.Cast<XmlNode>(), obj, tokens);
						return tree;
					}
					else if(obj->GetType()==L"Document")
					{
						vl::Ptr<XmlDocument> tree = new XmlDocument;
						vl::collections::CopyFrom(tree->creatorRules, obj->GetCreatorRules());
						Fill(tree, obj, tokens);
						Fill(tree.Cast<XmlNode>(), obj, tokens);
						return tree;
					}
					else 
						return 0;
				}
			};

			vl::Ptr<vl::parsing::ParsingTreeCustomBase> XmlConvertParsingTreeNode(vl::Ptr<vl::parsing::ParsingTreeNode> node, const vl::collections::List<vl::regex::RegexToken>& tokens)
			{
				XmlTreeConverter converter;
				vl::Ptr<vl::parsing::ParsingTreeCustomBase> tree;
				converter.SetMember(tree, node, tokens);
				return tree;
			}

/***********************************************************************
Parsing Tree Conversion Implementation
***********************************************************************/

			vl::Ptr<XmlText> XmlText::Convert(vl::Ptr<vl::parsing::ParsingTreeNode> node, const vl::collections::List<vl::regex::RegexToken>& tokens)
			{
				return XmlConvertParsingTreeNode(node, tokens).Cast<XmlText>();
			}

			vl::Ptr<XmlCData> XmlCData::Convert(vl::Ptr<vl::parsing::ParsingTreeNode> node, const vl::collections::List<vl::regex::RegexToken>& tokens)
			{
				return XmlConvertParsingTreeNode(node, tokens).Cast<XmlCData>();
			}

			vl::Ptr<XmlAttribute> XmlAttribute::Convert(vl::Ptr<vl::parsing::ParsingTreeNode> node, const vl::collections::List<vl::regex::RegexToken>& tokens)
			{
				return XmlConvertParsingTreeNode(node, tokens).Cast<XmlAttribute>();
			}

			vl::Ptr<XmlComment> XmlComment::Convert(vl::Ptr<vl::parsing::ParsingTreeNode> node, const vl::collections::List<vl::regex::RegexToken>& tokens)
			{
				return XmlConvertParsingTreeNode(node, tokens).Cast<XmlComment>();
			}

			vl::Ptr<XmlElement> XmlElement::Convert(vl::Ptr<vl::parsing::ParsingTreeNode> node, const vl::collections::List<vl::regex::RegexToken>& tokens)
			{
				return XmlConvertParsingTreeNode(node, tokens).Cast<XmlElement>();
			}

			vl::Ptr<XmlInstruction> XmlInstruction::Convert(vl::Ptr<vl::parsing::ParsingTreeNode> node, const vl::collections::List<vl::regex::RegexToken>& tokens)
			{
				return XmlConvertParsingTreeNode(node, tokens).Cast<XmlInstruction>();
			}

			vl::Ptr<XmlDocument> XmlDocument::Convert(vl::Ptr<vl::parsing::ParsingTreeNode> node, const vl::collections::List<vl::regex::RegexToken>& tokens)
			{
				return XmlConvertParsingTreeNode(node, tokens).Cast<XmlDocument>();
			}

/***********************************************************************
Parser Function
***********************************************************************/

			vl::Ptr<vl::parsing::ParsingTreeNode> XmlParseDocumentAsParsingTreeNode(const vl::WString& input, vl::Ptr<vl::parsing::tabling::ParsingTable> table, vl::collections::List<vl::Ptr<vl::parsing::ParsingError>>& errors, vl::vint codeIndex)
			{
				vl::parsing::tabling::ParsingState state(input, table, codeIndex);
				state.Reset(L"XDocument");
				vl::Ptr<vl::parsing::tabling::ParsingGeneralParser> parser=vl::parsing::tabling::CreateStrictParser(table);
				vl::Ptr<vl::parsing::ParsingTreeNode> node=parser->Parse(state, errors);
				return node;
			}

			vl::Ptr<vl::parsing::ParsingTreeNode> XmlParseDocumentAsParsingTreeNode(const vl::WString& input, vl::Ptr<vl::parsing::tabling::ParsingTable> table, vl::vint codeIndex)
			{
				vl::collections::List<vl::Ptr<vl::parsing::ParsingError>> errors;
				return XmlParseDocumentAsParsingTreeNode(input, table, errors, codeIndex);
			}

			vl::Ptr<XmlDocument> XmlParseDocument(const vl::WString& input, vl::Ptr<vl::parsing::tabling::ParsingTable> table, vl::collections::List<vl::Ptr<vl::parsing::ParsingError>>& errors, vl::vint codeIndex)
			{
				vl::parsing::tabling::ParsingState state(input, table, codeIndex);
				state.Reset(L"XDocument");
				vl::Ptr<vl::parsing::tabling::ParsingGeneralParser> parser=vl::parsing::tabling::CreateStrictParser(table);
				vl::Ptr<vl::parsing::ParsingTreeNode> node=parser->Parse(state, errors);
				if(node && errors.Count()==0)
				{
					return XmlConvertParsingTreeNode(node, state.GetTokens()).Cast<XmlDocument>();
				}
				return 0;
			}

			vl::Ptr<XmlDocument> XmlParseDocument(const vl::WString& input, vl::Ptr<vl::parsing::tabling::ParsingTable> table, vl::vint codeIndex)
			{
				vl::collections::List<vl::Ptr<vl::parsing::ParsingError>> errors;
				return XmlParseDocument(input, table, errors, codeIndex);
			}

			vl::Ptr<vl::parsing::ParsingTreeNode> XmlParseElementAsParsingTreeNode(const vl::WString& input, vl::Ptr<vl::parsing::tabling::ParsingTable> table, vl::collections::List<vl::Ptr<vl::parsing::ParsingError>>& errors, vl::vint codeIndex)
			{
				vl::parsing::tabling::ParsingState state(input, table, codeIndex);
				state.Reset(L"XElement");
				vl::Ptr<vl::parsing::tabling::ParsingGeneralParser> parser=vl::parsing::tabling::CreateStrictParser(table);
				vl::Ptr<vl::parsing::ParsingTreeNode> node=parser->Parse(state, errors);
				return node;
			}

			vl::Ptr<vl::parsing::ParsingTreeNode> XmlParseElementAsParsingTreeNode(const vl::WString& input, vl::Ptr<vl::parsing::tabling::ParsingTable> table, vl::vint codeIndex)
			{
				vl::collections::List<vl::Ptr<vl::parsing::ParsingError>> errors;
				return XmlParseElementAsParsingTreeNode(input, table, errors, codeIndex);
			}

			vl::Ptr<XmlElement> XmlParseElement(const vl::WString& input, vl::Ptr<vl::parsing::tabling::ParsingTable> table, vl::collections::List<vl::Ptr<vl::parsing::ParsingError>>& errors, vl::vint codeIndex)
			{
				vl::parsing::tabling::ParsingState state(input, table, codeIndex);
				state.Reset(L"XElement");
				vl::Ptr<vl::parsing::tabling::ParsingGeneralParser> parser=vl::parsing::tabling::CreateStrictParser(table);
				vl::Ptr<vl::parsing::ParsingTreeNode> node=parser->Parse(state, errors);
				if(node && errors.Count()==0)
				{
					return XmlConvertParsingTreeNode(node, state.GetTokens()).Cast<XmlElement>();
				}
				return 0;
			}

			vl::Ptr<XmlElement> XmlParseElement(const vl::WString& input, vl::Ptr<vl::parsing::tabling::ParsingTable> table, vl::vint codeIndex)
			{
				vl::collections::List<vl::Ptr<vl::parsing::ParsingError>> errors;
				return XmlParseElement(input, table, errors, codeIndex);
			}

/***********************************************************************
Table Generation
***********************************************************************/

			vl::Ptr<vl::parsing::tabling::ParsingTable> XmlLoadTable()
			{
				vl::stream::MemoryStream stream;
				XmlGetParserBuffer(stream);
				vl::Ptr<vl::parsing::tabling::ParsingTable> table=new vl::parsing::tabling::ParsingTable(stream);
				table->Initialize();
				return table;
			}

		}
	}
}
