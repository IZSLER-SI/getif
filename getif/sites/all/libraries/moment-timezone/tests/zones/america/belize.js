"use strict";

var helpers = require("../../helpers/helpers");

exports["America/Belize"] = {

	"guess:by:offset" : helpers.makeTestGuess("America/Belize", { offset: true, expect: "America/Managua" }),

	"guess:by:abbr" : helpers.makeTestGuess("America/Belize", { abbr: true, expect: "America/Managua" }),

	"1918" : helpers.makeTestYear("America/Belize", [
		["1918-10-06T05:59:59+00:00", "23:59:59", "CST", 360],
		["1918-10-06T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1919" : helpers.makeTestYear("America/Belize", [
		["1919-02-09T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1919-02-09T05:30:00+00:00", "23:30:00", "CST", 360],
		["1919-10-05T05:59:59+00:00", "23:59:59", "CST", 360],
		["1919-10-05T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1920" : helpers.makeTestYear("America/Belize", [
		["1920-02-15T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1920-02-15T05:30:00+00:00", "23:30:00", "CST", 360],
		["1920-10-03T05:59:59+00:00", "23:59:59", "CST", 360],
		["1920-10-03T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1921" : helpers.makeTestYear("America/Belize", [
		["1921-02-13T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1921-02-13T05:30:00+00:00", "23:30:00", "CST", 360],
		["1921-10-02T05:59:59+00:00", "23:59:59", "CST", 360],
		["1921-10-02T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1922" : helpers.makeTestYear("America/Belize", [
		["1922-02-12T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1922-02-12T05:30:00+00:00", "23:30:00", "CST", 360],
		["1922-10-08T05:59:59+00:00", "23:59:59", "CST", 360],
		["1922-10-08T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1923" : helpers.makeTestYear("America/Belize", [
		["1923-02-11T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1923-02-11T05:30:00+00:00", "23:30:00", "CST", 360],
		["1923-10-07T05:59:59+00:00", "23:59:59", "CST", 360],
		["1923-10-07T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1924" : helpers.makeTestYear("America/Belize", [
		["1924-02-10T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1924-02-10T05:30:00+00:00", "23:30:00", "CST", 360],
		["1924-10-05T05:59:59+00:00", "23:59:59", "CST", 360],
		["1924-10-05T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1925" : helpers.makeTestYear("America/Belize", [
		["1925-02-15T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1925-02-15T05:30:00+00:00", "23:30:00", "CST", 360],
		["1925-10-04T05:59:59+00:00", "23:59:59", "CST", 360],
		["1925-10-04T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1926" : helpers.makeTestYear("America/Belize", [
		["1926-02-14T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1926-02-14T05:30:00+00:00", "23:30:00", "CST", 360],
		["1926-10-03T05:59:59+00:00", "23:59:59", "CST", 360],
		["1926-10-03T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1927" : helpers.makeTestYear("America/Belize", [
		["1927-02-13T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1927-02-13T05:30:00+00:00", "23:30:00", "CST", 360],
		["1927-10-02T05:59:59+00:00", "23:59:59", "CST", 360],
		["1927-10-02T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1928" : helpers.makeTestYear("America/Belize", [
		["1928-02-12T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1928-02-12T05:30:00+00:00", "23:30:00", "CST", 360],
		["1928-10-07T05:59:59+00:00", "23:59:59", "CST", 360],
		["1928-10-07T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1929" : helpers.makeTestYear("America/Belize", [
		["1929-02-10T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1929-02-10T05:30:00+00:00", "23:30:00", "CST", 360],
		["1929-10-06T05:59:59+00:00", "23:59:59", "CST", 360],
		["1929-10-06T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1930" : helpers.makeTestYear("America/Belize", [
		["1930-02-09T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1930-02-09T05:30:00+00:00", "23:30:00", "CST", 360],
		["1930-10-05T05:59:59+00:00", "23:59:59", "CST", 360],
		["1930-10-05T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1931" : helpers.makeTestYear("America/Belize", [
		["1931-02-15T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1931-02-15T05:30:00+00:00", "23:30:00", "CST", 360],
		["1931-10-04T05:59:59+00:00", "23:59:59", "CST", 360],
		["1931-10-04T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1932" : helpers.makeTestYear("America/Belize", [
		["1932-02-14T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1932-02-14T05:30:00+00:00", "23:30:00", "CST", 360],
		["1932-10-02T05:59:59+00:00", "23:59:59", "CST", 360],
		["1932-10-02T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1933" : helpers.makeTestYear("America/Belize", [
		["1933-02-12T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1933-02-12T05:30:00+00:00", "23:30:00", "CST", 360],
		["1933-10-08T05:59:59+00:00", "23:59:59", "CST", 360],
		["1933-10-08T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1934" : helpers.makeTestYear("America/Belize", [
		["1934-02-11T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1934-02-11T05:30:00+00:00", "23:30:00", "CST", 360],
		["1934-10-07T05:59:59+00:00", "23:59:59", "CST", 360],
		["1934-10-07T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1935" : helpers.makeTestYear("America/Belize", [
		["1935-02-10T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1935-02-10T05:30:00+00:00", "23:30:00", "CST", 360],
		["1935-10-06T05:59:59+00:00", "23:59:59", "CST", 360],
		["1935-10-06T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1936" : helpers.makeTestYear("America/Belize", [
		["1936-02-09T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1936-02-09T05:30:00+00:00", "23:30:00", "CST", 360],
		["1936-10-04T05:59:59+00:00", "23:59:59", "CST", 360],
		["1936-10-04T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1937" : helpers.makeTestYear("America/Belize", [
		["1937-02-14T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1937-02-14T05:30:00+00:00", "23:30:00", "CST", 360],
		["1937-10-03T05:59:59+00:00", "23:59:59", "CST", 360],
		["1937-10-03T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1938" : helpers.makeTestYear("America/Belize", [
		["1938-02-13T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1938-02-13T05:30:00+00:00", "23:30:00", "CST", 360],
		["1938-10-02T05:59:59+00:00", "23:59:59", "CST", 360],
		["1938-10-02T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1939" : helpers.makeTestYear("America/Belize", [
		["1939-02-12T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1939-02-12T05:30:00+00:00", "23:30:00", "CST", 360],
		["1939-10-08T05:59:59+00:00", "23:59:59", "CST", 360],
		["1939-10-08T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1940" : helpers.makeTestYear("America/Belize", [
		["1940-02-11T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1940-02-11T05:30:00+00:00", "23:30:00", "CST", 360],
		["1940-10-06T05:59:59+00:00", "23:59:59", "CST", 360],
		["1940-10-06T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1941" : helpers.makeTestYear("America/Belize", [
		["1941-02-09T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1941-02-09T05:30:00+00:00", "23:30:00", "CST", 360],
		["1941-10-05T05:59:59+00:00", "23:59:59", "CST", 360],
		["1941-10-05T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1942" : helpers.makeTestYear("America/Belize", [
		["1942-02-15T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1942-02-15T05:30:00+00:00", "23:30:00", "CST", 360],
		["1942-10-04T05:59:59+00:00", "23:59:59", "CST", 360],
		["1942-10-04T06:00:00+00:00", "00:30:00", "-0530", 330]
	]),

	"1943" : helpers.makeTestYear("America/Belize", [
		["1943-02-14T05:29:59+00:00", "23:59:59", "-0530", 330],
		["1943-02-14T05:30:00+00:00", "23:30:00", "CST", 360]
	]),

	"1973" : helpers.makeTestYear("America/Belize", [
		["1973-12-05T05:59:59+00:00", "23:59:59", "CST", 360],
		["1973-12-05T06:00:00+00:00", "01:00:00", "CDT", 300]
	]),

	"1974" : helpers.makeTestYear("America/Belize", [
		["1974-02-09T04:59:59+00:00", "23:59:59", "CDT", 300],
		["1974-02-09T05:00:00+00:00", "23:00:00", "CST", 360]
	]),

	"1982" : helpers.makeTestYear("America/Belize", [
		["1982-12-18T05:59:59+00:00", "23:59:59", "CST", 360],
		["1982-12-18T06:00:00+00:00", "01:00:00", "CDT", 300]
	])
};