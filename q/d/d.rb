#!/usr/bin/env ruby

require 'pp'

def rec(okeys, akeys, ikeys, opened, ohist, ahist)
  if okeys.size == opened.size
    pp opened
    opened
  else
    ohist.each do |i, o|
      if o > ahist[i]
        puts "hit! depth=#{opened.size}"
        return nil
      end
    end
    r = nil
    okeys.each_with_index do |o, i|
      next if opened.include?(i)
      j = ikeys.index(o)
      next if j.nil?
      opened2 = opened+[i]
      next if r && (r <=> opened2) < 0
      ikeys2 = ikeys.dup
      ikeys2.delete_at(j)
      ohist2 = ohist.dup
      ohist2[o] -= 1
      ahist2 = ahist.dup
      ahist2[o] -= 1
      s = rec(okeys, akeys, ikeys2+akeys[i], opened2, ohist2, ahist2)
      next if s.nil?
      r = s if r.nil? || (s <=> r) < 0
    end
    puts "abort: #{opened.join " "}" if r.nil?
    r
  end
end

t = gets.to_i

t.times do |i|
  okeys = []
  akeys = []
  ohist = {}
  ohist.default = 0
  ahist = {}
  ahist.default = 0
  k, n = gets.chomp.split.map(&:to_i)
  ikeys = gets.chomp.split.map(&:to_i)
  ikeys.each do |j|
    ahist[j] += 1
  end
  n.times do
    ak = gets.chomp.split.map(&:to_i)
    okeys << ak.shift
    ak.shift
    akeys << ak
    ak.each do |j|
      ahist[j] += 1
    end
  end
  okeys.each do |j|
    ohist[j] += 1
  end
  pp [okeys, akeys, ikeys, ohist, ahist]
  r = rec(okeys, akeys, ikeys, [], ohist, ahist)
  puts "Case ##{i+1}: #{r ? r.map(&:next).join(" ") : "IMPOSSIBLE"}"
end
