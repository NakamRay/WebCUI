#!/usr/bin/perl --

use CGI;
use strict;
use warnings;

# read the CGI params
my $cgi = CGI->new;
my $ip = $cgi->param("ip");
my $rs = $cgi->param("rs");
my $pro = $cgi->param("pro");
my $form = $cgi->param("form");
my $hasGhcRules = $cgi->param("hasGhcRules");
#my $form = "hs";
my $tool = $cgi->param("tool");
#my $area = $cgi->param('area');
my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = localtime(time);
my $time = time;
my $year1 = ($year+1900)%100;
my $mtime = sprintf('_%02d%02d%02d_%02d%02d', $year1, $mon+1,$mday,$hour, $min);

my $tmpfilePrefix = "log/c$ip$mtime";
my $tmpfile = "";
if ("$form" eq "haskell") {
    $tmpfile = "$tmpfilePrefix.hs";
} else {
    $tmpfile = "$tmpfilePrefix.$form";
}
# my $tmpfile = "log/c$mtime.$form";

print $cgi->header('text/plain;charset=UTF-8');

open (FILE, ,">", $tmpfile) or die "$!";
print FILE $rs;
close (FILE);

my $timeout = "timeout 10";
my $command = "";

if ("$hasGhcRules" eq "true" && "$form" eq "haskell" && ("$pro" eq "cri" || "$pro" eq "snG" || "$pro" eq "cr")){ # run solhask
    if ("$pro" eq "snG") {
        $pro = "sn";
    }
    $command = " ./gsol-wrapper.sh $pro $tmpfile ";

} elsif ("$hasGhcRules" eq "false") { # run sol
  if ("$pro" eq "cr" || "$pro" eq "sn") {
      # confluence (cr) or terminaton (sn) checking
      $command = " $timeout ./Main $pro $tmpfile --sol= 2>&1";
  } elsif ("$pro" eq "snG") {
      # termination checking wiht the general schema
      $command = " $timeout ./Main sn $tmpfile --sol=GS 2>&1";
  #} elsif ("$pro" eq "cr_CBV") {
  #    $command = " $timeout ./Main $pro $tmpfile --sol=CBV 2>&1";
  #} elsif ("$pro" eq "acph") {
  #    $command = " $timeout ./Main cr $tmpfile --acph 2>&1";
  #} elsif ("$pro" eq "csiho") {
  #    $command = " $timeout ./Main cr $tmpfile --csiho 2>&1";
  #} elsif ("$pro" eq "wanda") {
  #    $command = " $timeout ./Main sn $tmpfile --wanda=\"\" 2>&1";
  } else {
      $command = " echo \"fatal error: the combination of the format and command is impossible.\" 2>&1";
  }
} else {
      $command = " echo \"fatal error: the combination of the format and command is impossible.\" 2>&1";
  }


my @ret = `$command`;

foreach (@ret) {
    print $_;
}
