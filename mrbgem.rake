MRuby::Gem::Specification.new('mruby-require') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Internet Initiative Japan Inc., Kevin A. Smith'

  spec.cc.include_paths << "#{build.root}/src"
end

