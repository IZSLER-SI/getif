"use strict";

var helpers = require("../../helpers/helpers");

exports["Australia/Eucla"] = {

	"guess:by:offset" : helpers.makeTestGuess("Australia/Eucla", { offset: true }),

	"guess:by:abbr" : helpers.makeTestGuess("Australia/Eucla", { abbr: true }),

	"1916" : helpers.makeTestYear("Australia/Eucla", [
		["1916-12-31T15:15:59+00:00", "00:00:59", "+0845", -525],
		["1916-12-31T15:16:00+00:00", "01:01:00", "+0945", -585]
	]),

	"1917" : helpers.makeTestYear("Australia/Eucla", [
		["1917-03-24T16:14:59+00:00", "01:59:59", "+0945", -585],
		["1917-03-24T16:15:00+00:00", "01:00:00", "+0845", -525]
	]),

	"1941" : helpers.makeTestYear("Australia/Eucla", [
		["1941-12-31T17:14:59+00:00", "01:59:59", "+0845", -525],
		["1941-12-31T17:15:00+00:00", "03:00:00", "+0945", -585]
	]),

	"1942" : helpers.makeTestYear("Australia/Eucla", [
		["1942-03-28T16:14:59+00:00", "01:59:59", "+0945", -585],
		["1942-03-28T16:15:00+00:00", "01:00:00", "+0845", -525],
		["1942-09-26T17:14:59+00:00", "01:59:59", "+0845", -525],
		["1942-09-26T17:15:00+00:00", "03:00:00", "+0945", -585]
	]),

	"1943" : helpers.makeTestYear("Australia/Eucla", [
		["1943-03-27T16:14:59+00:00", "01:59:59", "+0945", -585],
		["1943-03-27T16:15:00+00:00", "01:00:00", "+0845", -525]
	]),

	"1974" : helpers.makeTestYear("Australia/Eucla", [
		["1974-10-26T17:14:59+00:00", "01:59:59", "+0845", -525],
		["1974-10-26T17:15:00+00:00", "03:00:00", "+0945", -585]
	]),

	"1975" : helpers.makeTestYear("Australia/Eucla", [
		["1975-03-01T17:14:59+00:00", "02:59:59", "+0945", -585],
		["1975-03-01T17:15:00+00:00", "02:00:00", "+0845", -525]
	]),

	"1983" : helpers.makeTestYear("Australia/Eucla", [
		["1983-10-29T17:14:59+00:00", "01:59:59", "+0845", -525],
		["1983-10-29T17:15:00+00:00", "03:00:00", "+0945", -585]
	]),

	"1984" : helpers.makeTestYear("Australia/Eucla", [
		["1984-03-03T17:14:59+00:00", "02:59:59", "+0945", -585],
		["1984-03-03T17:15:00+00:00", "02:00:00", "+0845", -525]
	]),

	"1991" : helpers.makeTestYear("Australia/Eucla", [
		["1991-11-16T17:14:59+00:00", "01:59:59", "+0845", -525],
		["1991-11-16T17:15:00+00:00", "03:00:00", "+0945", -585]
	]),

	"1992" : helpers.makeTestYear("Australia/Eucla", [
		["1992-02-29T17:14:59+00:00", "02:59:59", "+0945", -585],
		["1992-02-29T17:15:00+00:00", "02:00:00", "+0845", -525]
	]),

	"2006" : helpers.makeTestYear("Australia/Eucla", [
		["2006-12-02T17:14:59+00:00", "01:59:59", "+0845", -525],
		["2006-12-02T17:15:00+00:00", "03:00:00", "+0945", -585]
	]),

	"2007" : helpers.makeTestYear("Australia/Eucla", [
		["2007-03-24T17:14:59+00:00", "02:59:59", "+0945", -585],
		["2007-03-24T17:15:00+00:00", "02:00:00", "+0845", -525],
		["2007-10-27T17:14:59+00:00", "01:59:59", "+0845", -525],
		["2007-10-27T17:15:00+00:00", "03:00:00", "+0945", -585]
	]),

	"2008" : helpers.makeTestYear("Australia/Eucla", [
		["2008-03-29T17:14:59+00:00", "02:59:59", "+0945", -585],
		["2008-03-29T17:15:00+00:00", "02:00:00", "+0845", -525],
		["2008-10-25T17:14:59+00:00", "01:59:59", "+0845", -525],
		["2008-10-25T17:15:00+00:00", "03:00:00", "+0945", -585]
	])
};