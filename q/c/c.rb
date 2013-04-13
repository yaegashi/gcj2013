#!/usr/bin/env ruby

require 'pp'

def fair?(x)
  s = x.to_s
  a = 0
  b = s.length - 1
  while a < b
    return false unless s[a] == s[b]
    a += 1
    b -= 1
  end
  return true;
end

def scan(a, b)
  c = 0
  smin = Math.sqrt(a).to_i
  smax = Math.sqrt(b).to_i
  smin.upto(smax) do |s|
    next unless fair?(s)
    ss = s*s
    next if ss < a
    c += 1 if fair?(ss)
  end
  return c
end

t = gets.to_i

t.times do |i|
  a, b = gets.chomp.split.map(&:to_i)
  puts "Case ##{i+1}: #{scan(a, b)}"
end

