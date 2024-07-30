"use strict";

var helpers = require("../../helpers/helpers");

exports["Asia/Manila"] = {

	"guess:by:offset" : helpers.makeTestGuess("Asia/Manila", { offset: true }),

	"guess:by:abbr" : helpers.makeTestGuess("Asia/Manila", { abbr: true }),

	"1899" : helpers.makeTestYear("Asia/Manila", [
		["1899-05-10T15:55:59+00:00", "23:59:59", "LMT", -484],
		["1899-05-10T15:56:00+00:00", "23:56:00", "PST", -480]
	]),

	"1936" : helpers.makeTestYear("Asia/Manila", [
		["1936-10-31T15:59:59+00:00", "23:59:59", "PST", -480],
		["1936-10-31T16:00:00+00:00", "01:00:00", "PDT", -540]
	]),

	"1937" : helpers.makeTestYear("Asia/Manila", [
		["1937-01-31T14:59:59+00:00", "23:59:59", "PDT", -540],
		["1937-01-31T15:00:00+00:00", "23:00:00", "PST", -480]
	]),

	"1942" : helpers.makeTestYear("Asia/Manila", [
		["1942-04-30T15:59:59+00:00", "23:59:59", "PST", -480],
		["1942-04-30T16:00:00+00:00", "01:00:00", "JST", -540]
	]),

	"1944" : helpers.makeTestYear("Asia/Manila", [
		["1944-10-31T14:59:59+00:00", "23:59:59", "JST", -540],
		["1944-10-31T15:00:00+00:00", "23:00:00", "PST", -480]
	]),

	"1954" : helpers.makeTestYear("Asia/Manila", [
		["1954-04-11T15:59:59+00:00", "23:59:59", "PST", -480],
		["1954-04-11T16:00:00+00:00", "01:00:00", "PDT", -540],
		["1954-06-30T14:59:59+00:00", "23:59:59", "PDT", -540],
		["1954-06-30T15:00:00+00:00", "23:00:00", "PST", -480]
	]),

	"1978" : helpers.makeTestYear("Asia/Manila", [
		["1978-03-21T15:59:59+00:00", "23:59:59", "PST", -480],
		["1978-03-21T16:00:00+00:00", "01:00:00", "PDT", -540]
	])
};