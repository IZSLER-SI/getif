"use strict";

var helpers = require("../../helpers/helpers");

exports["Asia/Ulaanbaatar"] = {

	"guess:by:offset" : helpers.makeTestGuess("Asia/Ulaanbaatar", { offset: true }),

	"guess:by:abbr" : helpers.makeTestGuess("Asia/Ulaanbaatar", { abbr: true }),

	"1977" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1977-12-31T16:59:59+00:00", "23:59:59", "+07", -420],
		["1977-12-31T17:00:00+00:00", "01:00:00", "+08", -480]
	]),

	"1983" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1983-03-31T15:59:59+00:00", "23:59:59", "+08", -480],
		["1983-03-31T16:00:00+00:00", "01:00:00", "+09", -540],
		["1983-09-30T14:59:59+00:00", "23:59:59", "+09", -540],
		["1983-09-30T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1984" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1984-03-31T15:59:59+00:00", "23:59:59", "+08", -480],
		["1984-03-31T16:00:00+00:00", "01:00:00", "+09", -540],
		["1984-09-29T14:59:59+00:00", "23:59:59", "+09", -540],
		["1984-09-29T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1985" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1985-03-30T15:59:59+00:00", "23:59:59", "+08", -480],
		["1985-03-30T16:00:00+00:00", "01:00:00", "+09", -540],
		["1985-09-28T14:59:59+00:00", "23:59:59", "+09", -540],
		["1985-09-28T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1986" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1986-03-29T15:59:59+00:00", "23:59:59", "+08", -480],
		["1986-03-29T16:00:00+00:00", "01:00:00", "+09", -540],
		["1986-09-27T14:59:59+00:00", "23:59:59", "+09", -540],
		["1986-09-27T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1987" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1987-03-28T15:59:59+00:00", "23:59:59", "+08", -480],
		["1987-03-28T16:00:00+00:00", "01:00:00", "+09", -540],
		["1987-09-26T14:59:59+00:00", "23:59:59", "+09", -540],
		["1987-09-26T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1988" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1988-03-26T15:59:59+00:00", "23:59:59", "+08", -480],
		["1988-03-26T16:00:00+00:00", "01:00:00", "+09", -540],
		["1988-09-24T14:59:59+00:00", "23:59:59", "+09", -540],
		["1988-09-24T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1989" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1989-03-25T15:59:59+00:00", "23:59:59", "+08", -480],
		["1989-03-25T16:00:00+00:00", "01:00:00", "+09", -540],
		["1989-09-23T14:59:59+00:00", "23:59:59", "+09", -540],
		["1989-09-23T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1990" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1990-03-24T15:59:59+00:00", "23:59:59", "+08", -480],
		["1990-03-24T16:00:00+00:00", "01:00:00", "+09", -540],
		["1990-09-29T14:59:59+00:00", "23:59:59", "+09", -540],
		["1990-09-29T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1991" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1991-03-30T15:59:59+00:00", "23:59:59", "+08", -480],
		["1991-03-30T16:00:00+00:00", "01:00:00", "+09", -540],
		["1991-09-28T14:59:59+00:00", "23:59:59", "+09", -540],
		["1991-09-28T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1992" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1992-03-28T15:59:59+00:00", "23:59:59", "+08", -480],
		["1992-03-28T16:00:00+00:00", "01:00:00", "+09", -540],
		["1992-09-26T14:59:59+00:00", "23:59:59", "+09", -540],
		["1992-09-26T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1993" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1993-03-27T15:59:59+00:00", "23:59:59", "+08", -480],
		["1993-03-27T16:00:00+00:00", "01:00:00", "+09", -540],
		["1993-09-25T14:59:59+00:00", "23:59:59", "+09", -540],
		["1993-09-25T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1994" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1994-03-26T15:59:59+00:00", "23:59:59", "+08", -480],
		["1994-03-26T16:00:00+00:00", "01:00:00", "+09", -540],
		["1994-09-24T14:59:59+00:00", "23:59:59", "+09", -540],
		["1994-09-24T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1995" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1995-03-25T15:59:59+00:00", "23:59:59", "+08", -480],
		["1995-03-25T16:00:00+00:00", "01:00:00", "+09", -540],
		["1995-09-23T14:59:59+00:00", "23:59:59", "+09", -540],
		["1995-09-23T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1996" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1996-03-30T15:59:59+00:00", "23:59:59", "+08", -480],
		["1996-03-30T16:00:00+00:00", "01:00:00", "+09", -540],
		["1996-09-28T14:59:59+00:00", "23:59:59", "+09", -540],
		["1996-09-28T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1997" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1997-03-29T15:59:59+00:00", "23:59:59", "+08", -480],
		["1997-03-29T16:00:00+00:00", "01:00:00", "+09", -540],
		["1997-09-27T14:59:59+00:00", "23:59:59", "+09", -540],
		["1997-09-27T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"1998" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["1998-03-28T15:59:59+00:00", "23:59:59", "+08", -480],
		["1998-03-28T16:00:00+00:00", "01:00:00", "+09", -540],
		["1998-09-26T14:59:59+00:00", "23:59:59", "+09", -540],
		["1998-09-26T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"2001" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["2001-04-27T17:59:59+00:00", "01:59:59", "+08", -480],
		["2001-04-27T18:00:00+00:00", "03:00:00", "+09", -540],
		["2001-09-28T16:59:59+00:00", "01:59:59", "+09", -540],
		["2001-09-28T17:00:00+00:00", "01:00:00", "+08", -480]
	]),

	"2002" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["2002-03-29T17:59:59+00:00", "01:59:59", "+08", -480],
		["2002-03-29T18:00:00+00:00", "03:00:00", "+09", -540],
		["2002-09-27T16:59:59+00:00", "01:59:59", "+09", -540],
		["2002-09-27T17:00:00+00:00", "01:00:00", "+08", -480]
	]),

	"2003" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["2003-03-28T17:59:59+00:00", "01:59:59", "+08", -480],
		["2003-03-28T18:00:00+00:00", "03:00:00", "+09", -540],
		["2003-09-26T16:59:59+00:00", "01:59:59", "+09", -540],
		["2003-09-26T17:00:00+00:00", "01:00:00", "+08", -480]
	]),

	"2004" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["2004-03-26T17:59:59+00:00", "01:59:59", "+08", -480],
		["2004-03-26T18:00:00+00:00", "03:00:00", "+09", -540],
		["2004-09-24T16:59:59+00:00", "01:59:59", "+09", -540],
		["2004-09-24T17:00:00+00:00", "01:00:00", "+08", -480]
	]),

	"2005" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["2005-03-25T17:59:59+00:00", "01:59:59", "+08", -480],
		["2005-03-25T18:00:00+00:00", "03:00:00", "+09", -540],
		["2005-09-23T16:59:59+00:00", "01:59:59", "+09", -540],
		["2005-09-23T17:00:00+00:00", "01:00:00", "+08", -480]
	]),

	"2006" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["2006-03-24T17:59:59+00:00", "01:59:59", "+08", -480],
		["2006-03-24T18:00:00+00:00", "03:00:00", "+09", -540],
		["2006-09-29T16:59:59+00:00", "01:59:59", "+09", -540],
		["2006-09-29T17:00:00+00:00", "01:00:00", "+08", -480]
	]),

	"2015" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["2015-03-27T17:59:59+00:00", "01:59:59", "+08", -480],
		["2015-03-27T18:00:00+00:00", "03:00:00", "+09", -540],
		["2015-09-25T14:59:59+00:00", "23:59:59", "+09", -540],
		["2015-09-25T15:00:00+00:00", "23:00:00", "+08", -480]
	]),

	"2016" : helpers.makeTestYear("Asia/Ulaanbaatar", [
		["2016-03-25T17:59:59+00:00", "01:59:59", "+08", -480],
		["2016-03-25T18:00:00+00:00", "03:00:00", "+09", -540]
	])
};